from random import randint
from time import time
import asyncio

async def multiply_by(lst, num):
    print(f"Multiplying by {num}...")
    res = []
    for i in lst:
        res.append(i*num)
    return sorted(res)

async def leave_even(lst):
    print(f"Deleting odds...")
    res = []
    for i in range(len(lst)):
        if i % 2 == 0:
            res.append(i)
    return sorted(res)

async def leave_case(lst):
    _max = max(lst)
    print(f"Leaving in the interval: {0.4*_max}<=x<= {0.6*_max}...")
    res = []
    for i in range(len(lst)):
        if 0.4*_max < i < 0.6*_max:
            res.append(i)
    return sorted(res)


def _main():
    AMOUNT = 200000
    lists = [randlist(AMOUNT) for i in range(3)]

    functions = [
        asyncio.ensure_future(multiply_by(lists[0], 5)),
        asyncio.ensure_future(leave_even(lists[1])),
        asyncio.ensure_future(leave_case(lists[2])),
    ]

    event_loop = asyncio.get_event_loop()
    event_loop.run_until_complete(asyncio.gather(*functions))
    event_loop.close()

    result = lmulti + leven + lcase

if __name__ == '__main__':
    _main()
