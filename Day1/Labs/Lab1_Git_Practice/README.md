# Lab 1: Git Practice

This lab will guide you through the process of using Git for version control.

## Objectives

*   Clone a repository.
*   Create a new branch.
*   Make changes to a file.
*   Commit and push changes.
*   Create a pull request.

## Instructions

1.  **Clone the workshop repository:**

    ```bash
    git clone <repository_url>
    ```

2.  **Create a new branch:**

    ```bash
    git checkout -b my-first-branch
    ```

3.  **Create a new file:**

    Create a new file named `hello.txt` with the following content:

    ```
    Hello, World!
    ```

4.  **Add and commit the file:**

    ```bash
    git add hello.txt
    git commit -m "Add hello.txt"
    ```

5.  **Push the changes to your forked repository:**

    ```bash
    git push origin my-first-branch
    ```

6.  **Create a pull request:**

    Go to the GitHub website and create a pull request to merge your changes into the main workshop repository.
