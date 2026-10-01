# DSTR codebase - original implementations preserved

This version keeps the supplied `array.cpp` and `linkedlist.cpp` unchanged.

## Files

- `array.cpp` - original array implementation, unchanged
- `linkedlist.cpp` - original linked-list implementation, unchanged
- `array.h` - declarations for the array implementation
- `linkedlist.h` - declarations for the linked-list implementation
- `implementations.cpp` - wraps the two original `.cpp` files in namespaces without editing them
- `main.cpp` - new main program

## Why implementations.cpp exists

The original files both contain their own `main()` and many identically named functions/globals. Rather than editing those files, `implementations.cpp` includes each original file inside a namespace:

- `Array::...`
- `LinkedList::...`

The original files remain unchanged on disk.

## Single dataset read

`main.cpp` has `loadDatasetOnce()`. It opens the CSV once, parses each row once, then puts that row into:

- `Array::patientList`
- `Array::unsortedPatientList`
- `LinkedList::patientNode`
- `LinkedList::unsortedPatientNode`

It therefore does not call the original `readFromDataset()` twice.

## Compile

```bash
g++ -std=c++17 -O0 -Wall -Wextra -pedantic main.cpp implementations.cpp -o patient_dstr
```

Run:

```bash
./patient_dstr
```
