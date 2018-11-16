# Assingment

In this project we'll create a C++ class that allows us to manipulate dates. The format of the date is so called Gregorian date which in practical terms mean the dates used in European countries:

The class you will implement is able to store and manipulate Gregorian format dates. The public interface should offer at least methods for:
- Creating and initializing a date object.
- Setting the value of a date object so that nonexisting dates will be rejected (with a suitable return value indicating success or failure).
- dA separate method for each to find out (as a return value) the date object's day, month, and year number.
- Printing the date stored in the object on the screen.
- Incrementing and decrementing the date object: in other words methods that will move the date one day forward and backward.
- What weekday is the date stored in the object. This is something you need to research or use your imagination. To simplify things the method you implement only needs to work correctly from 1.1.1800 forward.

Note! The only method which is allowed to output something using cout is the print method. None of the methods is allowed to use cin. The purpose of this extra requirements is to force everyone to design an interface which works based on method parameters and return values.