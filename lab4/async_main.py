from random import randint
from time import time
import asyncio 

async def randlist(amount):
    res = []
    for i in range(amount):
        res.append(randint(1, 100))
    return res

async def multiply_by(lst, num):
    print(f"Multiplying by {num}...")
    res = list(map(lambda x: x*num, lst))
    return sorted(res)

async def leave_even(lst):
    print(f"Deleting odds...")
    res = list(filter(lambda x: x % 2 == 0, lst))
    return sorted(res)

async def leave_case(lst):
    _max = max(lst)
    print(f"Leaving in the interval: {0.4*_max}<=x<= {0.6*_max}...")
    res = list(filter(lambda x: 0.4*_max <= x <= 0.6*_max, lst))
    return sorted(res)

def _main():
    AMOUNT = 200000
    start = time()
    lists = [randlist(AMOUNT) for i in range(3)]
    #print("List 1:", lists[0])
    #print("List 2:", lists[1])
    #print("List 3:", lists[2])

    lmulti = await multiply_by(lists[0], 5)
    #print(lmulti)
    leven = await leave_even(lists[1])
    #print(leven)
    lcase = await leave_case(lists[2])
    #print(lcase)
    result = lmulti + leven + lcase
    stop = time()
    duration = stop - start
    print("Duration: ", duration)

if __name__ == '__main__':
    _main()
