# class Student

Definition of a Student in the program.

## Variables

```cpp
private String name;
```

Name of the student. Can have up to 15 (English) characters.

```cpp
private String id;
```

Student ID of the student. Should have 10 digits, where first 4 digits represent admission year, next 3 digits represent department code, and next 3 digits represent serial number.

e.g., Student ID *2020038001*

| Admission year | Department Code | Serial number |
|----------------|-----------------|---------------|
| 2020           | 038             | 001           |

<br/>

```cpp
private String email;
```

Email address of the student. Can have up to 15 (English) characters. Preferably should be formatted as email address.

```cpp
private String tel;
```

Phone number of the student. Can have up to 12 digits.

```cpp
private String department_name;
```

Department name of the student.

## Constructor

```cpp
Student()
```

Instantiates the `Student` object.

```cpp
Student(String name, String id, String email, String tel)
```

Instantiates the `Student` object.

```cpp
Student(String name, String id, String email, String tel, string department_name)
```

Instantiates the `Student` object.

## Member functions

### Setters

```cpp
void set_name(string name);
```

Sets the name of the student object.

```cpp
void set_id(string id);
```

Sets the student ID of the student object.

```cpp
void set_email(string email);
```

Sets the email address of the student object.

```cpp
void set_tel(string tel);
```

Sets the phone number of the student object.

```cpp
void set_department_name(string department_name);
```

Sets the department name of the student object.

### Getters

```cpp
String get_name();
```

Returns the name of the student object.

#### Returns

- name of the object.

```cpp
String get_id();
```

Returns the student ID of the student object.

#### Returns

- student ID of the object. Should have 10 digit number in `string`.

```cpp
String get_email();
```

Returns the email address of the student object.

#### Returns

- email address of the object.

```cpp
String get_tel();
```

Returns the phone number of the student object.

#### Returns

- phone number of the object. Can have up to 12 digits.

- email address of the object.

```cpp
String get_department_name();
```

Returns the department name of the student object.

#### Returns

- Department name of the object.

