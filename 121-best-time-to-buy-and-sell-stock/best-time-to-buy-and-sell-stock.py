class Solution(object):

  def maxProfit(self, prices):
    """:type prices: List[int]

    :rtype: int
    """
    if not prices:
      return 0

    min_price = prices[0]
    max_profit = 0

    for price in prices[1:]:
      # Update the minimum price seen so far
      if price < min_price:
        min_price = price
      # Calculate potential profit and update max_profit if it's higher
      elif price - min_price > max_profit:
        max_profit = price - min_price

    return max_profit