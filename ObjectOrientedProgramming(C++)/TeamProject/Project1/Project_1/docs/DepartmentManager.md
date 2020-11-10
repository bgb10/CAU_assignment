# class DepartmentManager

Manages instantiated `Department` objects in the program.

## Variables

```cpp
private vector<Department> department_list;
```

Collection of the `Department` objects.

## Constructor

```cpp
DepartmentManager()
```

Instantiates the `DepartmentManager` object.

## Member functions

```cpp
public void InsertDepartment(Department department)
```

Insert `Department` object in `department_list`.

```cpp
public string FindName(string code)
```

Finds corresponding `name` from `departments` by searching `code`.

```cpp
public bool IsCodeExists(string code)
```

Find `code` from `deprtments`


```cpp
public bool IsNameExists(string name);
```

Find `name` from `departments`

#### Parameters

- `department_code` : three digit department code.

```cpp
public string FindCode(string name)
```

Finds corresponding `code` from `departments` by searching `name`.

### Setters

```cpp
public void set_department_list(vector<Department> department_list);
```

Reads `department_list` and copy into its own vector `department_list`.

### Getters

```cpp
public int get_department_count();
```

Returns the size of `department_list`.

```cpp
public vector<Department> get_department_list();
```

Returns `department_list`.

#### Returns

- number of `Department` objects in the current object.
