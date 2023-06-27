# TableClass Implementation and Query Operations

This repository contains the implementation of the `tableClass` class and various methods in C++ for performing queries on tabular data. The project was completed as part of the Data Structures course in Spring 2023.

## Objective
The goal of this project was to create a `tableClass` class and implement the specified methods outlined in the project description. These methods allow reading a CSV file, performing operations on the stored data, and displaying queried contents from the `tableClass`. The `tableClass` represents a table of data with rows and columns, where all the data is stored as strings.

## Description
In this project, the main focus was on implementing the `tableClass` class and its associated methods as provided in the `boilerplate_project2.cpp` file. The data in the table can be of different types, such as categorical and numeric, all stored as strings. It's important to handle data type conversions dynamically, performing late binding to convert strings to the desired data types when required for calculations.

The project supported several operations and queries, including finding records based on a specific value, searching for a value in the entire table, displaying the table data, finding the minimum value in a column, returning a subset of columns and/or rows, and more. These operations were specified by command options in the input file and were performed on the sorted table.

An exception handling mechanism was implemented to handle cases where invalid operations are performed, such as searching for a non-existent name or calculating statistics on non-numeric columns. An exception class and a set of exceptions were defined to handle such cases.

## Input Explanation
The input file format for the project was as follows:

<name of file input>
<data types of columns>
<number of rows>
<number of columns>
<commands/options for operations and queries>

The input file started with the name of the file to be read, followed by the data types of the columns in the table. The number of rows and columns in the table were specified next. After that, a list of commands/options for various operations and queries was provided, which extended until the end of the input file. All row and column numbers were zero-indexed.

The commands/options available for operations and queries were as follows:
- `F`: Find the record/row and return the entire row. The query value is the first column's value.
- `V`: Find the value in the entire table and display all the row and column numbers where it appears.
- `D`: Display the `myTable` data.
- `I`: Find the minimum value of the given column number.
- `C`: Return a `tableClass` object with a subset of columns and all rows from the two given column numbers.
- `R`: Return a `tableClass` object with a subset of rows and all columns from the two given row numbers.
- `S`: Return a `tableClass` object with a subset of rows and columns from the two given row and column numbers.

The input file also mentioned the need to throw exceptions in specific cases, such as searching for a non-existent name or performing operations on non-numeric columns.

## CSV File
The project involved reading a CSV file containing the tabular data. The CSV file format was expected to match the following structure:

        <column 0> <column 1> ... <column n-1>
        <row 0>
        <row 1>
        ...
        <row m-1>

Each row in the CSV file represented a record, and each column contained a value. The values could be numbers or names, all stored as strings. The CSV file had to be read using file input/output functionalities (fstream) and the appropriate parsing techniques.

