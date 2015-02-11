# Test eval function

x1 = 0
x2 = 1
cnt = 10

def foo():

   if cnt <= 0:
      println "All done!"
      return 0
   end

   next = "f_" + str(cnt)
   ::eval(next) = x1
   println ::eval(next)

   y = x1
   x1 = x2
   x2 = y + x2

   cnt = cnt - 1
   foo()

end

foo()
__debug__
