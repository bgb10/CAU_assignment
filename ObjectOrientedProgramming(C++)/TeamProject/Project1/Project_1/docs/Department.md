# class Department

Definition of a **department** in the program.

## Variables

```cpp
private string name;
```

Name of the department. (e.g., Computer Science)

```cpp
private string code;
```

Code of the department. (e.g., 038)

Consisted of three digit number, as seen in the middle of Student ID.

e.g., Student ID *2020038001*

| Admission year | Department Code | Serial number |
|----------------|-----------------|---------------|
| 2020           | ***038***       | 001           |

## Constructor

```cpp
Department(String code, String name)
```

Instantiates the `Department` object.

```cpp
Department()
```

Instantiates the `Department` object.

## Member functions

### Getters

```cpp
string get_code();
```

Returns the `code` of the department.

#### Returns

- 3 digit number code of the department in `string`.

```cpp
string get_name();
```

Returns the `name` of the department.

#### Returns

- name of the department.

### Setters

```cpp
void set_code(string code);
```

Sets the `code` of the department.
Code should be 3 digit number code in `string`.

```cpp
void set_name(string name);
```

Sets the `name` of the department.