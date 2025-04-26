# CS-210-Project-Three
A C++ program that tracks grocery purchases with a menu interface. Integrates Python for data processing and displays item frequencies, specific item counts, and histograms based on sales data. Ideal for demonstrating C++ and Python interoperability.

## 🛒 Corner Grocer Tracker - Project Reflection

### 🔍 Summary of the Project
This project, *Corner Grocer Tracker*, is a C++ program designed to help users track grocery purchases through a simple, menu-driven interface. It connects with a Python script to perform core functionalities like retrieving item frequencies, generating a histogram of purchase data, and looking up specific items. The project solves the problem of efficiently analyzing purchase frequency from a text-based inventory without using a database, making it ideal for small businesses or learning environments.

### ✅ What I Did Well
One of the strongest aspects of this project is the seamless integration between C++ and Python. Using Python's strengths for text processing and data handling, while leveraging C++ for interface and control flow, made the program modular and efficient. I also kept the code readable by encapsulating functionality within methods and maintaining consistent naming conventions.

### 🛠️ Areas for Improvement
The code could be improved by adding more robust error handling and input validation, especially for file operations and user input. Currently, the program assumes that the Python script and data files exist and function correctly. Adding try-catch blocks and fallback messages would make the application more fault-tolerant and secure. Also, using `std::getline()` instead of `cin >>` could better handle multi-word item names.

### ⚠️ Common Challenge Encountered
A common issue developers may face with this project is correctly setting up and calling Python functions from C++. Handling Python's C API can be error-prone, especially if you forget to check for `nullptr` or don’t manage memory properly. I overcame this by carefully referencing documentation and using `PyErr_Print()` frequently during debugging to trace failures in Python function calls.

### 🔁 Transferable Skills
This project helped me develop practical experience with inter-language integration, specifically using the Python/C API. This is a valuable skill when working with systems that require multiple programming languages. Additionally, I gained experience designing modular code, handling user input, and reading from files—skills applicable in nearly every software development scenario.

### 🧹 Maintainability and Readability
To keep the program clean and easy to maintain, I used descriptive naming, kept each function focused on a single task, and grouped related features within a class. The use of helper functions for repetitive tasks (like drawing the histogram) also makes the code more adaptable for future changes. If another developer picks up this project, the structure and inline comments should make it easy to understand and extend.
