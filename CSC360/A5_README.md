Assignment 4

 The following paragraphs outline how I implemented each of the page replacement algorithms required for this assignment.
 note: these algorithms are also explained to lesser detail as comments in virtmem.c 

 FIFO ALGORITHM 

 Instead of using a queue to implement this algorithm I created a new variable in the page_table_entry struct called fifo_count. When a new page is added to the page table, I initialize this value to 0. Each time a new instruction is read, I increment the value of fifo_count for every page in the page table by one. This way, the page with the highest fifo_count has been in the table the longest and therefore was the "first in". This logic occures in the fifo_algorithm function (where I loop through the page table looking for the highest fifo_count, which will be chosen as the victum frame). 

 LFU ALGORITHM 

 For this algorithm, I added a new variable in the page_table_entry struct called lfu_count. This value is initialized to 0 in setup. When a new page is added to the table, I set the value to 1 (as this page has been used once). Each time a page is used, I increment its lfu_count by one. The logic for this algorithm occures in the lfu_algorithm function. This function loops through the page table and picks the page with the lowest lfu_count as the victum frame (as this page has been used the least).  In the case of a tie break (if 2 pages have the same lfu count) page that was added to the table first will be the victum frame. 

 CLOCK ALGORITHM 

 This algorithm relies on 2 global variables, clock_front_hand, clock_back_hand that act as the 2 clock hands (they hold the index that the clock hands point to). This algorithm also relies on the struct var called "clock_bit". This is used to keep track of which pages have been given a second chance. The front clock hand points to the page according to the fifo algorithm (at first will point to the index fifo returns, as the clock hand moves along it points to the next fifo index (added to the table after the first victim frame etc)). 

 The distance between the front hand and back hand is one. The value of the back hand is changed in the fifo_algorithm function (back hand points to the "second page" in ). The back hand will unset bits that it points to. As the front hand moves, it sets the bits of the pages it points to. If the front hand points to a page with a bit that has already been set, it choses this page to be the victim frame and returns this index. This logic happens in the clock_algorithm() function. 

 Please note: The reason for this distance of 1 is because it was the easiest way to keep track of the fifo order (with my array based solution). If I were to do this assignment again I would use a queue as this solution gave me lots of trouble in the clock algorithm...
