class Jar:
    def __init__(self, capacity=12):
        self.cap = capacity
        self.total = 0
        if capacity < 0:
            raise ValueError('Capacity cannot be negative')

    def __str__(self):
        return self.total * '🍪'

    def deposit(self, n):
        self.put = n
        if self.total + n > self.capacity:
            raise ValueError('Capacity exceeded')
        self.total += n

    def withdraw(self, n):
        self.take = n
        if self.total - n < 0:
            raise ValueError('Not enough cookies')
        self.total -= n

    @property
    def capacity(self):
        return self.cap

    @property
    def size(self):
        return self.total

def main():
    jar = Jar()
    jar.deposit(0)
    jar.withdraw(1)
    print(str(jar.capacity))
    print(str(jar))

main()