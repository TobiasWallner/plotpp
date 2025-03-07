#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

int main() {
    int pipe_in[2];  // Pipe for sending data to gnuplot (parent -> child)
    int pipe_out[2]; // Pipe for reading data from gnuplot (child -> parent)
    
    if (pipe(pipe_in) == -1 || pipe(pipe_out) == -1) {
        std::cerr << "Pipe creation failed!" << std::endl;
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    if (pid == 0) {  // Child process
        // Redirect stdin to pipe_in[0] (read end of pipe_in)
        dup2(pipe_in[0], STDIN_FILENO);
        // Redirect stdout to pipe_out[1] (write end of pipe_out)
        dup2(pipe_out[1], STDOUT_FILENO);

        // Close unused pipe ends
        close(pipe_in[1]);
        close(pipe_out[0]);

        // Execute gnuplot
        execlp("gnuplot", "gnuplot", nullptr);
        std::cerr << "execlp failed!" << std::endl;
        return 1;
    } else {  // Parent process
        // Close unused pipe ends
        close(pipe_in[0]);
        close(pipe_out[1]);

        // Write gnuplot commands to the child process's stdin
        const char* commands = 
            "set terminal dumb size 60,20\n"
            "set title 'Simple XY Plot'\n"
            "plot '-' using 1:2 with lines title 'y = x^2'\n"
            "1 1\n"
            "2 4\n"
            "3 9\n"
            "4 16\n"
            "5 25\n"
            "e\n";
        
        write(pipe_in[1], commands, strlen(commands));
        close(pipe_in[1]);  // Close the write end to send EOF to the child process

        // Read the output from the child process's stdout (gnuplot)
        char buffer[256];
        std::string result;
        ssize_t count;
        while ((count = read(pipe_out[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[count] = '\0';
            result += buffer;
        }
        close(pipe_out[0]);

        // Wait for the child process to finish
        waitpid(pid, nullptr, 0);

        // Output the result (the gnuplot ASCII graph)
        std::cout << "Gnuplot output:\n" << result << std::endl;
    }

    return 0;
}
