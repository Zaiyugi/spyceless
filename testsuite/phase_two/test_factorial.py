def fact(x):
   if x == 1.0:
      return 1.0
   else:
      return x * fact(x-1.0)
   end
end

def loop(cnt, max):
   if cnt < max:
      println str(int(cnt)) + ": " + str(fact(cnt))
      cnt = cnt + 1.0
      loop(cnt, max)
   end
end

loop(1.0, 14.0)
