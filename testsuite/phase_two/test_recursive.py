x = 0
y = 10
def foo():
   if x > y:
      println "Back out"
      return 0
   end

   println str(x) + " " * (x+1) + "Recurse"
   x = x + 1
   foo()
end

foo()
