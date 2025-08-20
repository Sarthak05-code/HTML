roman_numerals = [
    (1000, 'M'),
    (900, 'CM'),
    (500, 'D'),
    (400, 'CD'),
    (100, 'C'),
    (90, 'XC'),
    (50, 'L'),
    (40, 'XL'),
    (10, 'X'),
    (9, 'IX'),
    (5, 'V'),
    (4, 'IV'),
    (1, 'I'),
]

def main():
    roman = ""
    int_number = int(input("Enter a number: "))
    for num, text in roman_numerals:
        while int_number >= num:
            roman += text
            int_number -= num
    print(roman)
   
main()