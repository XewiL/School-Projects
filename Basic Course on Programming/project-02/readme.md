 # Assingment
 
 Let's consider the following kind of information relating to the products and their prices in the different stores of the different grocery store chains:

    S-Market
        Hervantakeskus
            milk          1.05
            peanut butter 3.25
    S-Market
        Pirkkala
            peanut butter 2.90
            milk          2.00
    S-Market
        Kaukajärvi
            milk          1.05
            peanut butter 3.25
    K-Citymarket
        Pirkkala
            milk          0.95
            peanut butter 2.90
    K-Citymarket
        Turtola
            peanut butter 4.20
            milk          0.95
    K-Citymarket
        Lielahti
            peanut butter 3.00
            milk          0.95
    K-Citymarket
        Linnainmaa
            milk          0.95
            peanut butter 2.90
    Prisma
        Kaleva
            milk          0.90
            peanut butter 2.90
    Prisma
        Lielahti
            milk          1.90
            peanut butter 2.90
    Prisma
        Koivistonkylä
            peanut butter 2.90
            milk          0.90
  

Even if the list above has exactly the same two products listed for every single store, this is of course not true generally: different stores have different selection. All the stores don't carry the same products. For example, Pirkka products can only be found in K-stores.

The product selection information shown above can be represented using csv-file like this:

    store_chain;store_location;product_name;product_price
  
The example used above would look like this when stored in a csv-file:

    S-Market;Hervantakeskus;milk;1.05
    Prisma;Koivistonkyla;peanut_butter;2.90
    S-Market;Hervantakeskus;peanut_butter;3.25
    S-Market;Pirkkala;milk;2.00
    K-Citymarket;Linnainmaa;peanut_butter;2.90
    S-Market;Kaukajarvi;peanut_butter;3.25
    K-Citymarket;Pirkkala;milk;0.95
    Prisma;Kaleva;peanut_butter;2.90
    K-Citymarket;Pirkkala;peanut_butter;2.90
    Prisma;Lielahti;milk;1.90
    K-Citymarket;Turtola;peanut_butter;4.20
    S-Market;Kaukajarvi;milk;1.05
    K-Citymarket;Lielahti;milk;0.95
    K-Citymarket;Linnainmaa;milk;0.95
    Prisma;Kaleva;milk;0.90
    Prisma;Lielahti;peanut_butter;2.90
    S-Market;Pirkkala;peanut_butter;2.90
    Prisma;Koivistonkyla;milk;0.90
    K-Citymarket;Lielahti;peanut_butter;3.00
    K-Citymarket;Turtola;milk;0.95
  
Every legal line has four semicolon separated fields. None of the fields are allowed to be empty or consist only of whitespace characters. The last field must represent a real number (double).

To keep things simple let's also agree that none of the fields can contain semicolon (;) or whitespace characters. In other words on an error free line there is always three semicolons, no whitespace characters, and none of the fields are empty.

Also notice, that the lines in the file can be in any order. It doesn't affect to the behaviour of the program.
The names of the store chains, store locations, and product names can contain any visible characters, except semicolons (as stated above).

If the same product is given to the same store more than once, the last one of them will be used as an actual value (price). For example:

    S-Market;Hervantakeskus;milk;0.55
    Prisma;Koivistonkyla;peanut_butter;2.90
    S-Market;Hervantakeskus;peanut_butter;3.25
    S-Market;Pirkkala;milk;2.00
    S-Market;Hervantakeskus;milk;1.05

The price of the milk in S-Market Hervantakeskus would end up being 1.05.

The program to be implemented is able to read a file in the format described above, store the information in some suitable combination of STL containers, and allow the user to make simple queries/searches into the information stored in the data structure. 