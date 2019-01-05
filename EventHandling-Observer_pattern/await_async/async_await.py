import types

@types.coroutine
def f():
   print('Line 1')
   result = yield 'someValue'
   print('The result is', result)


async def f_async():
   await f()
 
if __name__ == '__main__':
    try:
      g = f()
      g.send(None)
      g.send(123)
    except StopIteration:
      print("We're done")
      pass

    try:
      # g_async = await f() # cannot write this syntax, so next line
      g_async = f_async()	
      g_async.send(None)
      g_async.send(456)
    except StopIteration:
      print("We're done")
      pass


