/**
 * FILE: UnitTest_Full.cpp
 * MÔ TẢ: Kiểm thử đơn vị toàn diện cho Module Điều khiển Game 2048
 * PHẠM VI: Các hàm Up(), Down(), Left(), Right()
 * KỸ THUẬT: Kiểm thử hộp đen (Giá trị biên)
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// ====================================================
// PHẦN 1: MÔ PHỎNG LOGIC CŨ (UNIT UNDER TEST)
// ====================================================
// Lưu ý: Code dưới đây giữ nguyên logic "copy-paste" từ control.cpp
// để tái hiện lỗi tràn mảng (Index Out of Bounds).

void Testable_Left(int board[4][4], int &score) {
    // 1. Dồn số
    for (int i = 0; i < 4; i++) {
        int t = 0;
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 0) {
                board[i][t] = board[i][j];
                if(t != j) board[i][j] = 0;
                t++;
            }
        }
    }
    // 2. Gộp số (Lỗi biên phải: j=3 truy cập [i][4])
    for (int i = 0; i < 4; i++) {
        int t = 0;
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 0) {
                // BUG: Khi j=3, board[i][j+1] là ngoài mảng
                if (board[i][j] == board[i][j + 1]) {
                    board[i][t] = 2 * board[i][j];
                    score += board[i][t];
                    j++; t++;
                } else {
                    board[i][t] = board[i][j];
                    t++;
                }
            }
        }
        for (int j = t; j < 4; j++) board[i][j] = 0;
    }
}

void Testable_Right(int board[4][4], int &score) {
    // 1. Dồn số
    for (int i = 0; i < 4; i++) {
        int t = 3;
        for (int j = 3; j >= 0; j--) {
            if (board[i][j] != 0) {
                board[i][t] = board[i][j];
                if(t != j) board[i][j] = 0;
                t--;
            }
        }
    }
    // 2. Gộp số (Lỗi biên trái: j=0 truy cập [i][-1])
    for (int i = 0; i < 4; i++) {
        int t = 3;
        for (int j = 3; j >= 0; j--) {
            if (board[i][j] != 0) {
                // BUG: Khi j=0, board[i][j-1] là board[i][-1]
                if (board[i][j] == board[i][j - 1]) {
                    board[i][t] = 2 * board[i][j];
                    score += board[i][t];
                    j--; t--;
                } else {
                    board[i][t] = board[i][j];
                    t--;
                }
            }
        }
        for (int j = t; j >= 0; j--) board[i][j] = 0;
    }
}

void Testable_Up(int board[4][4], int &score) {
    // 1. Dồn số
    for (int j = 0; j < 4; j++) {
        int t = 0;
        for (int i = 0; i < 4; i++) {
            if (board[i][j] != 0) {
                board[t][j] = board[i][j];
                if(t != i) board[i][j] = 0;
                t++;
            }
        }
    }
    // 2. Gộp số (Lỗi biên dưới: i=3 truy cập [4][j])
    for (int j = 0; j < 4; j++) {
        int t = 0;
        for (int i = 0; i < 4; i++) {
            if (board[i][j] != 0) {
                // BUG: Khi i=3, board[i+1][j] là board[4][j]
                if (board[i][j] == board[i + 1][j]) {
                    board[t][j] = 2 * board[i][j];
                    score += board[t][j];
                    t++; i++;
                } else {
                    board[t][j] = board[i][j];
                    t++;
                }
            }
        }
        for (int i = t; i < 4; i++) board[i][j] = 0;
    }
}

void Testable_Down(int board[4][4], int &score) {
    // 1. Dồn số
    for (int j = 0; j < 4; j++) {
        int t = 3;
        for (int i = 3; i >= 0; i--) {
            if (board[i][j] != 0) {
                board[t][j] = board[i][j];
                if(t != i) board[i][j] = 0;
                t--;
            }
        }
    }
    // 2. Gộp số (Lỗi biên trên: i=0 truy cập [-1][j])
    for (int j = 0; j < 4; j++) {
        int t = 3;
        for (int i = 3; i >= 0; i--) {
            if (board[i][j] != 0) {
                // BUG: Khi i=0, board[i-1][j] là board[-1][j]
                if (board[i][j] == board[i - 1][j]) {
                    board[t][j] = 2 * board[i][j];
                    score += board[t][j];
                    t--; i--;
                } else {
                    board[t][j] = board[i][j];
                    t--;
                }
            }
        }
        for (int i = t; i >= 0; i--) board[i][j] = 0;
    }
}

// ====================================================
// PHẦN 2: MÔI TRƯỜNG TEST (TEST HARNESS)
// ====================================================

// Struct này giúp ta kiểm soát bộ nhớ xung quanh bàn cờ
// Để gài bẫy (padding) phát hiện việc truy cập tràn mảng
struct TestEnv {
    int pad_top[4];     // Vùng nhớ đệm phía trên (Bắt lỗi index -1)
    int board[4][4];    // Bàn cờ chính
    int pad_bottom[4];  // Vùng nhớ đệm phía dưới (Bắt lỗi index 4)
} env;

void resetEnv() {
    for(int i=0; i<4; i++) {
        env.pad_top[i] = 0;
        env.pad_bottom[i] = 0;
        for(int j=0; j<4; j++) env.board[i][j] = 0;
    }
}

// ====================================================
// PHẦN 3: MAIN - CHẠY TEST CASE
// ====================================================

int main() {
    cout << "==========================================================" << endl;
    cout << "BAO CAO KIEM THU TOAN DIEN (FULL COVERAGE) - GAME 2048" << endl;
    cout << "==========================================================" << endl << endl;

    int totalErrors = 0;
    int score = 0;

    // --- 1. KIỂM THỬ HÀM LEFT ---
    {
        cout << "[TEST] Function: Left()... ";
        resetEnv();
        // Setup: Hàng 0 đầy đủ [2,4,8,16]. Mong đợi không đổi.
        env.board[0][0]=2; env.board[0][1]=4; env.board[0][2]=8; env.board[0][3]=16;

        // GÀI BẪY: Trong C++, board[0][4] chính là ô đầu tiên hàng dưới (board[1][0])
        // Ta gán giá trị 16 vào đây. Nếu code lỗi, nó sẽ gộp 16(cuối hàng) với 16(rác).
        env.board[1][0] = 16;

        Testable_Left(env.board, score);

        if (env.board[0][3] == 32) { // 16+16=32 (Sai)
            cout << "FAIL (Loi tran mang phai)" << endl;
            totalErrors++;
        } else cout << "PASS" << endl;
    }

    // --- 2. KIỂM THỬ HÀM RIGHT ---
    {
        cout << "[TEST] Function: Right()... ";
        resetEnv();
        // Setup: Hàng 1 đầy đủ [16,8,4,2].
        env.board[1][0]=16; env.board[1][1]=8; env.board[1][2]=4; env.board[1][3]=2;

        // GÀI BẪY: board[1][-1] chính là ô cuối của hàng trên (board[0][3])
        env.board[0][3] = 16;

        Testable_Right(env.board, score);

        if (env.board[1][0] == 32) { // 16 gộp với rác 16 thành 32
            cout << "FAIL (Loi tran mang trai)" << endl;
            totalErrors++;
        } else cout << "PASS" << endl;
    }

    // --- 3. KIỂM THỬ HÀM UP ---
    {
        cout << "[TEST] Function: Up()... ";
        resetEnv();
        // Setup: Cột 0 đầy đủ [2,4,8,16] theo chiều dọc
        env.board[0][0]=2; env.board[1][0]=4; env.board[2][0]=8; env.board[3][0]=16;

        // GÀI BẪY: board[4][0] nằm ở vùng đệm dưới (pad_bottom)
        env.pad_bottom[0] = 16;

        Testable_Up(env.board, score);

        if (env.board[3][0] == 32) {
            cout << "FAIL (Loi tran mang duoi)" << endl;
            totalErrors++;
        } else cout << "PASS" << endl;
    }

    // --- 4. KIỂM THỬ HÀM DOWN ---
    {
        cout << "[TEST] Function: Down()... ";
        resetEnv();
        // Setup: Cột 0 đầy đủ [16,8,4,2] theo chiều dọc
        env.board[0][0]=16; env.board[1][0]=8; env.board[2][0]=4; env.board[3][0]=2;

        // GÀI BẪY: board[-1][0] nằm ở vùng đệm trên (pad_top)
        // Lưu ý: Việc truy cập ngược mảng phụ thuộc vào compiler,
        // nhưng logic code chắc chắn sai vì i chạy về 0 rồi check i-1.
        env.pad_top[0] = 16;

        Testable_Down(env.board, score);

        if (env.board[0][0] == 32) {
            cout << "FAIL (Loi tran mang tren)" << endl;
            totalErrors++;
        } else {
            // Ngay cả khi không gộp sai, việc truy cập chỉ số âm là lỗi nghiêm trọng
            // Ta đánh dấu FAIL để cảnh báo rủi ro Crash
            cout << "FAIL (Loi truy cap chi so am [-1])" << endl;
            totalErrors++;
        }
    }

    // ====================================================
    // TỔNG KẾT METRICS
    // ====================================================
    cout << endl << "--- UNIT TEST SUMMARY ---" << endl;
    double kloc = 0.160; // 4 hàm x 40 dòng = 160 dòng
    cout << "Total LOC: " << (kloc*1000) << " lines" << endl;
    cout << "KLOC: " << kloc << endl;
    cout << "Total Defects Found: " << totalErrors << endl;
    cout << "Defect Density: " << (totalErrors / kloc) << " Errors/KLOC" << endl;

    if (totalErrors > 0) {
        cout << "KET LUAN: Code can Refactor gap!" << endl;
    }

    return 0;
}