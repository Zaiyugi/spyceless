x1 = 0
x2 = 1
cnt = 25
def foo():

   println x1

   y = x1
   x1 = x2
   x2 = y + x2

   if cnt < 0:
      println "All done!"
      return 0
   end

   cnt = cnt - 1
   foo()

end

foo()
