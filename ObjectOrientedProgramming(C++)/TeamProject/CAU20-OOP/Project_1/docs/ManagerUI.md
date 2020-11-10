# class ManagerUI

A class that provides an interface for the manager to interact with users.

## Variables

```cpp
private StudentManager* stud_manager
```

```cpp
private DepartmentManager* dept_manager
```
## Constructor

```cpp
ManagerUI(StudentManager& stud_manager, DepartmentManager& dept_manager)
```

After receiving StudentManager and DepartMentManager, Instantiates the `ManagerUI` object.

#### Returns

- a newly created `ManagerUI`.

## Member functions

```cpp
public void Initialize()
```

Show the menu in Loop, then perform the functions below according to user input.

```cpp
private void StudentInsertion()
```

Displays the screen for the Insertion` menu and forwards the command to the StudentManager according to user input.

```cpp
private void Search()
```

Displays the screen for the `Search` menu and forwards the command to the StudentManager according to user input.
It also displays on the screen based on the results of the StudentManager.

```cpp
private void SetSortingOption()
```

Displays the screen for the `SetSortingOption` menu and forwards the command to the StudentManager according to user input.

```cpp
private void DepartmentInsertion()
```

Displays the screen for the `DepartmentInsertion` menu and forwards the command to the DepartmentManager according to user input.
