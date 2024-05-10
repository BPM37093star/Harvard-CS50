import re
from cs50 import get_string

amex_pattern = r'^(34|37)\d{13}$'
master_pattern = r'^(5[1-5])\d{14}$'
visa_pattern = r'^4\d{12}(\d{3})?$'

user_num = get_string("Number: ")
num_list = list(map(int, user_num))

def luhn_check(card_number):
    for i in range(len(card_number) - 2, -1, -2):
        card_number[i] *= 2
        if card_number[i] > 9:
            card_number[i] -= 9
    return sum(card_number) % 10

if re.match(amex_pattern, user_num):
    """
    double_sum = (num_list[1] + num_list[3] + num_list[5] + num_list[7] + num_list[9] + num_list[11] + num_list[13]) * 2
    simple_sum = num_list[0] + num_list[2] + num_list[4] + num_list[6] + num_list[8] + num_list[10] + num_list[12] + num_list[14]
    total = double_sum + simple_sum
    if total % 10 == 0:
        print("AMEX")
    """
    if luhn_check(num_list) == 0:
        print("AMEX")
    print("INVALID")
elif re.match(master_pattern, user_num):
    """
    double_sum = (num_list[0] + num_list[2] + num_list[4] + num_list[6] + num_list[8] + num_list[10] + num_list[12] + num_list[14]) * 2
    simple_sum = num_list[1] + num_list[3] + num_list[5] + num_list[7] + num_list[9] + num_list[11] + num_list[13] + num_list[15]
    total = double_sum + simple_sum
    """
    if luhn_check(num_list) == 0:
        print("MASTERCARD")
    print("INVALID")
elif re.match(visa_pattern, user_num):
    if len(num_list) == 13:
        """
        double_sum = (num_list[1] + num_list[3] + num_list[5] + num_list[7] + num_list[9] + num_list[11]) * 2
        simple_sum = num_list[0] + num_list[2] + num_list[4] + num_list[6] + num_list[8] + num_list[10] + num_list[12]
        total = double_sum + simple_sum
        """
        if luhn_check(num_list) == 0:
            print("VISA")
        print("INVALID")
    elif len(num_list) == 16:
        """
        double_sum = (num_list[0] + num_list[2] + num_list[4] + num_list[6] + num_list[8] + num_list[10] + num_list[12] + num_list[14]) * 2
        simple_sum = num_list[1] + num_list[3] + num_list[5] + num_list[7] + num_list[9] + num_list[11] + num_list[13] + num_list[15]
        total = double_sum + simple_sum
        """

        if luhn_check(num_list) == 0:
            print("VISA")
        print("INVALID")
else:
    print("INVALID")
