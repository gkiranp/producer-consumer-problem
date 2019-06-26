# Producer-Consumer-problem
A standard solution to a standard Producer-Consumer problem using C++11 

## Problem-Statement
Let's consider a situation in a restorant; for simplicity, let's assume there is only 1 cook/chef (producer) and 1 supplier (consumer). During a busy day, chef will produce as many as (unlimited) amount of meals and supplier has to serve them to the table. 

Go ahead and check my solution I submitted to above problem.

#Some explanation#:
1. There is a "buffer" associated with "Order" which both cook and supplier will have to look into. Imagine buffer as a kitchen room; idea is to keep buffer as small as possible, so that when cook produce the mael and put it into the buffer, it will be still `hot` by the time supplier supply to the customer.
2. If buffer is `empty` supplier has to wait until new order comes in and chef will produce the meal. If buffer is `full`, chef has to wait until supplier supplies one meal to the customer.
3. If you increase buffer size, you can achieve faster production process, however it will void our point 1. Hence, it is nominal to keep some delay between chef (higher delay in producing) and supplier (lesser delay in supply) inorder to achieve an average speed of sync as possible.

Go ahead run the code, you will see, at the begining, both chef and supplier are at their best speed of operation, and later after few seconds, they start lagging.
