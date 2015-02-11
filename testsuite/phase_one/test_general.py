# Test General

def foo():
   x = 50
   y = 30
   z = bar()

   sum = x + y + z
   prod = x * y * z

   println "X: " + str(x) + " | Y: " + str(y) + " | Z: " + str(z)
   println "Sum: " + str(sum)
   println "Product: " + str(prod)

   println "x%y: " + str(x%y)
   println "x/double(y): " + str(x / double(y))

   println "Debug: "
   __debug__

end

def bar():
   a = 3
   b = 2
   c = 4

   return -( (a*b - c)**c % 3.4 )
end

foo() 
