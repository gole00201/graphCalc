import math


def cnt_dig(number, base):
    '''Считаем число разрядов в системе, чтоб ыописать число'''
    return math.ceil(math.log(number + 1, base))


def change_sys(num, t):
    '''Возвращаем генератор со знаками числа в системе'''
    assert num > -1 and t >= 2
    cnt = 0
    dig = cnt_dig(num, t)
    while cnt != dig:
        left = num % t
        num = num // t
        cnt += 1
        yield left


def change_mult_sys(list_of_nums, t):
    '''Делаем change_sys для каждого элемента в списке
    вовзращаем генератор списков'''
    for num in list_of_nums:
        tmp = list(change_sys(num, t))
        tmp.reverse()
        yield tmp


def create_data(maunt):
    '''просто генерим список чисел'''
    return [i for i in range(maunt+1)]


if __name__ == "__main__":
    data = create_data(26)
    for i in change_mult_sys(data, 3):
        print(i)
