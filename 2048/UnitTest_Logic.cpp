#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// ====================================================
// PHẦN 1: UNIT CẦN KIỂM THỬ (Mô phỏng code cũ nhiều lỗi)
// ====================================================

// Hàm Left() được trích xuất và giữ nguyên các thói quen code "ẩu"
void Testable_Left(int board[4][4], int &currentScore)
{
    // [KLOC START] - Bắt đầu đếm dòng code (~40 dòng)

    // GIAI ĐOẠN 1: DỒN SỐ (SLIDE)
    for (int i = 0; i < 4; i++)
    {
        int t = 0;
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] != 0)
            {
                board[i][t] = board[i][j];
                // [DEFECT #1 - TIỀM ẨN]: Code cũ đôi khi quên xóa ô cũ sau khi dời
                // Nếu t != j mà không gán board[i][j] = 0 thì số cũ vẫn còn.
                // Ở đây giả lập là bạn QUÊN dòng: if (t!=j) board[i][j] = 0;
                t++;
            }
        }
    }

    // GIAI ĐOẠN 2: GỘP SỐ (MERGE)
    for (int i = 0; i < 4; i++)
    {
        int t = 0;
        // [DEFECT #2 - NGHIÊM TRỌNG]: Lỗi tràn mảng (Index Out of Bounds)
        // Vòng lặp chạy j đến 3, truy cập board[i][4]
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] != 0)
            {
                if (board[i][j] == board[i][j + 1])
                {
                    board[i][t] = 2 * board[i][j];

                    // [DEFECT #3 - LOGIC]: Tính điểm sai
                    // Lẽ ra phải cộng số mới (board[i][t]), nhưng lại cộng số cũ (board[i][j])
                    // Ví dụ: 4+4=8. Điểm phải cộng 8, nhưng code này chỉ cộng 4.
                    currentScore += board[i][j];

                    j++;
                    t++;
                }
                else
                {
                    board[i][t] = board[i][j];
                    t++;
                }
            }
        }

        // Đoạn này reset các ô thừa về 0.
        // Nhưng do lỗi ở Giai đoạn 1 (Ghost Tile), dữ liệu rác có thể vẫn còn tồn tại sai lệch.
        for (int j = t; j < 4; j++) board[i][j] = 0;
    }
    // [KLOC END]
}

// ====================================================
// PHẦN 2: CÁC HÀM HỖ TRỢ TEST (TEST RUNNER)
// ====================================================

void printActual(int board[4][4], int score) {
    cout << "   -> Actual Board: [ ";
    for(int j=0; j<4; j++) cout << board[0][j] << " ";
    cout << "] | Score: " << score << endl;
}

bool verifyRow0(int board[4][4], int e0, int e1, int e2, int e3) {
    if (board[0][0] != e0 || board[0][1] != e1 ||
        board[0][2] != e2 || board[0][3] != e3) return false;
    return true;
}

void setupBoard(int board[4][4], int r0, int r1, int r2, int r3) {
    for(int i=0; i<4; i++) for(int j=0; j<4; j++) board[i][j] = 0;
    board[0][0] = r0; board[0][1] = r1;
    board[0][2] = r2; board[0][3] = r3;
}

// ====================================================
// PHẦN 3: MAIN - CHẠY TEST CASE CHI TIẾT
// ====================================================

int main() {
    cout << "=================================================" << endl;
    cout << "ADVANCED UNIT TEST REPORT - GAME 2048 (C++)" << endl;
    cout << "Scope: Logic, Boundary, Score Calculation" << endl;
    cout << "=================================================" << endl << endl;

    int totalErrors = 0;
    int board[4][4] = {0};
    int score = 0;

    // ---------------------------------------------------------
    // TEST CASE 1: LỖI BÓNG MA (GHOST TILES) - DEFECT #1
    // Mục đích: Kiểm tra xem sau khi dồn số, số cũ có bị xóa không?
    // Input: [0, 2, 0, 4] -> Mong đợi: [2, 4, 0, 0]
    // ---------------------------------------------------------
    {
        string tcName = "TC_01 [Partition]: Don so (Ghost Tile Check)";
        setupBoard(board, 0, 2, 0, 4);
        score = 0;

        Testable_Left(board, score);

        // Nếu code bị lỗi #1, kết quả sẽ ra [2, 4, 0, 4] (số 4 cũ không bị xóa)
        if (verifyRow0(board, 2, 4, 0, 0)) {
            cout << tcName << " -> PASS" << endl;
        } else {
            cout << tcName << " -> FAIL (Loi du lieu rac/Ghost Tile)" << endl;
            printActual(board, score);
            totalErrors++;
        }
    }

    // ---------------------------------------------------------
    // TEST CASE 2: LỖI TRÀN MẢNG (INDEX OUT OF BOUND) - DEFECT #2
    // Mục đích: Kiểm tra truy cập ngoài biên mảng
    // Input: [2, 4, 8, 16] + Ô nhớ rác = 16
    // ---------------------------------------------------------
    {
        string tcName = "TC_02 [Boundary]: Tran mang (Index Out Of Bound)";
        setupBoard(board, 2, 4, 8, 16);
        board[1][0] = 16; // Gài bẫy ô nhớ rác

        Testable_Left(board, score);

        if (verifyRow0(board, 2, 4, 8, 16)) {
            cout << tcName << " -> PASS" << endl;
        } else {
            cout << tcName << " -> FAIL (Loi tran mang nghiem trong)" << endl;
            cout << "   [Giai thich]: Tru caap board[0][4] lay phai gia tri rac" << endl;
            printActual(board, score);
            totalErrors++;
        }
    }

    // ---------------------------------------------------------
    // TEST CASE 3: LỖI TÍNH ĐIỂM (SCORE LOGIC) - DEFECT #3
    // Mục đích: Kiểm tra điểm số cộng vào có đúng không?
    // Input: [4, 4, 0, 0] -> Mong đợi Board: [8, 0, 0, 0], Score += 8
    // ---------------------------------------------------------
    {
        string tcName = "TC_03 [Function]: Tinh diem (Score Logic)";
        setupBoard(board, 4, 4, 0, 0);
        score = 0;

        Testable_Left(board, score);

        // Kiểm tra cả Bàn cờ và Điểm số
        bool boardOK = verifyRow0(board, 8, 0, 0, 0);
        bool scoreOK = (score == 8);

        if (boardOK && scoreOK) {
            cout << tcName << " -> PASS" << endl;
        } else {
            cout << tcName << " -> FAIL (Loi logic tinh toan)" << endl;
            if (!boardOK) cout << "   [Board Error]: Sai cau truc mang" << endl;
            if (!scoreOK) cout << "   [Score Error]: Mong doi 8, Thuc te " << score << endl;
            printActual(board, score);
            totalErrors++;
        }
    }

    // ====================================================
    // TỔNG HỢP BÁO CÁO (METRICS)
    // ====================================================
    cout << endl << "--- FINAL METRICS ---" << endl;
    double kloc = 0.040; // Khoảng 40 dòng code logic
    cout << "Module Size: " << kloc << " KLOC" << endl;
    cout << "Total Defects Found: " << totalErrors << endl;

    // Tính tỷ lệ lỗi
    double density = (kloc > 0) ? (totalErrors / kloc) : 0;
    cout << "Defect Density: " << density << " Errors/KLOC" << endl;

    cout << "Danh gia chat luong: " << (density > 10 ? "RAT KEM (Can Refactor)" : "TOT") << endl;

    // Dừng màn hình
    // int pause; cin >> pause;
    return 0;
}