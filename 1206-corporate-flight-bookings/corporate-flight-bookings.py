class Solution:
    def corpFlightBookings(self, bookings: list[list[int]], n: int) -> list[int]:
        diff = [0] * (n + 1)
        for first, last, seats in bookings:
            diff[first - 1] += seats
            diff[last] -= seats
            
        # Accumulate prefix sums to get final flight seat counts
        res = [0] * n
        current_seats = 0
        for i in range(n):
            current_seats += diff[i]
            res[i] = current_seats
            
        return res