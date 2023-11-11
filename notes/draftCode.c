The Todo application offers a way to display tasks for the week, allowing users to easily observe
their work schedule.
The command to execute this feature is Show week. 
Below are the features of the weekly task
display in the Todo app currently being implemented.
The first line of the display consists of the days of the week and their respective dates. An
example content of a cell in the first line:
MON 16/10
The days in the first row start from Monday (MON) instead of Sunday (SUN). The cell in the top left corner displays the year of the current week instead of
"GMT+07" as in Figure 2. The first column displays hourly time milestones starting from
"00:00" (0 hour 0 minute), "01:00", "02:00", ..., "13:00" (1 in the afternoon),..., "23:00", "00:00".
This column counts the time in the day from 0 to 24 hours, instead of using 12 AM for morning
and 12 PM for afternoon. The strings in the cells of the first row and the first column must be
centered based on the width of the cell. The width of the cells in the first column is stored in
the variable WEEK_CELL_FIRST_COL_WIDTH. The width of the other cells outside
the first column is stored in the variable WEEK_CELL_OTHER_COL_WIDTH.
To print a string s with a length of ws, centered in a cell with a width of wc, we calculate
the number of white spaces p to print before printing string s as follows:
p = ⌊(wc − ws)/2⌋
Where, ⌊x⌋ is the operation to round down (floor) the value x.
Cells that are not in the first column and not in the first row represent tasks. A task may
require one cell or several consecutive cells for representation; we call the cells representing tasks
as the task cell block. When representing a task cell block, we do not depict lines connecting
the cells within the block. A detailed illustrative example will be provided at the submission
place on e-learning site. The information displayed on the screen for each block consists of two
lines. Line 1 contains the task number, start time, and end time of the task. Below is the format
of line 1, where <hh> and <mm> respectively represent hours and minutes, each comprising
two digits. <hh>, <mm> before the hyphen depict the start time. <hh>, <mm> after the
hyphen represent the end time. <num> is the task number.
#<num>|<hh>:<mm>-<hh>:<mm>
Line 2 records the task title. Note that a cell for a task only has a width of
WEEK_CELL_OTHER_COL_WIDTH. If the length of the task title is longer than
the cell width, the title is partially displayed, and three dots at the end indicate that the title
continues. Therefore, the title will be displayed three characters less than the cell width. The
last three characters are replaced with three ’.’ characters.
For simplicity, the Todo application being implemented will only display tasks for the week
if all tasks in that week have an even start and end time. An even time refers to a time with
the minute being "00". When a task in the week is detected with a non-even time, we consider
it as a task causing a display error for the week. Upon detecting a task causing an error, the
application calls the printUnsupportedTime(struct Task * task) function and passes the
task with a non-even time.
Requirement 19 (2.0 points): Implement the printWeekTime function with the
following descriptions:
• Function declaration: int printWeekTime(struct Task * array_tasks, int no_tasks,
char * date)
• Input:
– array_tasks: the address pointing to the first element of a tasks array
– no_tasks: the current number of elements in the array_tasks
– date: includes information about the day of the week, date, month, and year; this
date corresponds to <date> from the Show week time:[<date>] command
• Output: return a value of -1 if tasks can be displayed for the week. Otherwise, return
the position of the first task in the array_tasks that causes an error preventing a week
display.
• Function Requirements: Display tasks for the week as described earlier in this section.
The displayed week is determined by the date parameter. If unable to display for the
week, call the printUnsupportedTime function and pass the task causing the display
error. If there are multiple tasks causing the same error, print the first task from the start
of the array_tasks array