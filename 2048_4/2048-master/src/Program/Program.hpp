#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_
#include <vector>
#include <string>
/*!
 * \brief Static class for handling program existence and SDL events.
 */
class Program
{
    public:
        //! Starts the program
        //! \param args Const reference to command vector of line arguments. Unused.
        //! \return Exit code after program finishes. Unused.
        static int start(const std::vector<std::string>& args);

        //! Tells whether program is running
        //! \return True if running, false otherwise.
        static bool is_running() { return m_is_running; }

        //! Stops the program.
        //! \param force If provided, program will be closed violently.
        static void stop(bool force);

    private:
        static bool m_is_running; //!< Indicates whether program is running.
        static int m_ret_value; //!< Stores return value.

        // Disallow creation of instances
        Program() = delete;
        Program(Program&) = delete;
        Program(Program&&) = delete;
        Program& operator=(Program&) = delete;
        Program& operator=(Program&&) = delete;
};

#endif // _PROGRAM_HPP_
