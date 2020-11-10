# class StudentManager

Manages instantiated `Student` objects in the program.

## Variables

```cpp
private vector<Student> student_list;
```

Collection of the `Student` objects. Contains all of the student data in the running program.

```cpp
private int sort_option;
```

Current sorting option for search operation. Options are described as following.

| `sort_option` | Sorting order           |
|---------------|-------------------------|
| 1             | Sort by name            |
| 2             | Sort by student ID      |
| 3             | Sort by department name |

## Constructor

```cpp
StudentManager()
```

Instantiates the `StudentManager` object.

## Member functions

```cpp
public void InsertStudent(Student student)
```

Inserts given `Student` object into vector `student_list`.

```cpp
public vector<Student> SearchStudents(int search_option, string query)
```

Searches students with `search_option` and `query` and returns the results.

Search options and possible queries are described as following.

| `search_option` | Searching method                     | `query`                                   |
|-----------------|--------------------------------------|-------------------------------------------|
| 1               | Search by name                       | `name` of the `Student`                   |
| 2               | Search by student ID (10 numbers)    | 10 digit `id` of the `Student`            |
| 3               | Search by admission year (4 numbers) | Starting 4 digit of `id` of the `Student` |
| 4               | Search by department name            | `name` of the `Department`                |
| 5               | List all                             | `null`                                    |

#### Parameters

- `search_option` : the option to search students from all students. Should be an integer value between 1 and 4.
- `query` : the query to search students. Should be a non-empty string.

#### Returns

- if a student exists with the search options, a collection of `Student` objects corresponding to the given parameters. If no student exists, returns an empty `vector<Student>` object. This is same on the following `FindStudentBy...()` functions.

<br/>

```cpp
public vector<Student> FindStudentsByName(String name)
```

Finds students by `name` and returns `vector<Student>` objects.

This corresponds to *Search by name* action in *Search*.

```cpp
public vector<Student> FindStudentsByID(String id)
```

Finds students by `id` and returns `vector<Student>` objects.

This corresponds to *Search by ID* action in *Search*.

```cpp
public vector<Student> FindStudentsByAdmissionYear(String admission_year)
```

Finds students by `admission_year` and returns `vector<Student>` objects.

This corresponds to *Search by admission year* action in *Search*.

```cpp
public vector<Student> FindStudentsByDepartmentName(String department_name)
```

Finds students by `department_name` and returns `vector<Student>` objects.

This corresponds to *Search by department name* action in *Search*.

### Setters

```cpp
public void set_department_name(DepartmentManager dept_manager)
```

Use `dept_manager` to set each `student`'s department_name.

```cpp
public void set_student_list(vector<Student> student_list)
```

Reads `students_list` object and copy into its own vector `student_list`.

```cpp
public void set_sort_option(int sort_option);
```

Sets the `sort_option` for current object.

#### Parameters

- `sort_option` : the option to sort search results. Should be an integer value between 1 and 3.

```cpp
private void SortByName();
```

Sorts `vector<Student>` by `name`.

```cpp
private void SortByID();
```

Sorts `vector<Student>` by `id`.

```cpp
private void SortByDepartmentName();
```

Sorts `vector<Student>` by `department_name`.

### Getters

```cpp
public vector<Student> get_student_list();
```

Returns `student_list` in the current object.

```cpp
public int get_sort_option();
```

Returns the `sort_option` in the current object.

```cpp
public int get_student_count();
```

Returns the size of the `student_list` collection.

#### Returns

- number of `Student` objects in the current object.
