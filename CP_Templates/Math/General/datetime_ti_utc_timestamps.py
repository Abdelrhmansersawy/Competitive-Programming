# Convert Datetime to UTC Timestamp in Python
import calendar
from datetime import datetime

def getDate(s1 , s2):
  # s1: 2024-01-31  , s2: 23:99
  [year , month , day] = map(int , s1.split('-'))
  [hour , minute] = map(int , s2.split(':'))
  dt = datetime(year, month, day, hour, minute, 0)
  time_in_second = calendar.timegm(dt.utctimetuple())
  return int(time_in_second)
