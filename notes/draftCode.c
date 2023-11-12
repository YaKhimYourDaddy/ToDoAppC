char testcase_requirement1_commands[][12] = {
    "Add data",
    "Edit entry",
    "Show all",
    "Delete item",
    "Quit",
    "Invalid command",
    "Addd data",
    "edit entry",
    "SHOW all",
    "Dele",
    "  Quit ", // still valid cuz requirement does not say about this case
    "random string"};

char testcase_requirement2_addCommands[][10] = {
    // Check from left to right, one by one
    "Add [title] [description] [time]",    // valid
    "Add [title] [description [time]",     // invalid
    "Add [title] [description] [time",     // invalid
    "Add [[] [] []] [description] time",   // invalid
    "Add [[] [] []] [description] [time]", // valid
    "Add [[] [] []] [description [time]",  // invalid
    "Add [[] [] []] [description] [time",  // invalid
    "Add [[] [] []] [description] time]",  // invalid
    "Add [[] []] [[]] [time]",             // valid
    "Add [[title] [description] [time]]"   // valid
};

char testcase_requirement3_titles[][5] = {
    "Programming Assignment 1",
    "A very long title exceeding the maximum (100char) lengthhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh",
    "Invalid#CharacterInTitle",
    " Invalid Start Whitespace",
    "Invalid End Whitespace "};

char testcase_requirement4_description[][5] = {
    "This is a valid description.",
    "A very long description exceeding the maximum (200char) lengthhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh.",
    "Invalid#CharacterInDescription",
    " Invalid Start Whitespace",
    "Invalid End Whitespace "};

char testcase_requirement5_datetime[][10] = {
    "12:30|15/11/2023-16:45|15/11/2023",    // valid
    "-1101:30|15/11/2023-16:45|15/11/2023", // invalid input but requirement say nothing about this case, and I let hh==-1101 to show it can lead to result -1 like it is valid
    "25:30|15/11/2023-16:45|15/11/2023",    // invalid_hour1
    "12:30|15/11/2023-16:75|15/11/2023",    // invalid_mimute2
    "12:30|32/11/2023-16:45|15/11/2023",    // invalid_day1
    "12:30|15/13/2023-16:45|15/11/2023",    // invalid_month1
    "12:30|15/11/0000-16:45|15/11/2023",    // invalid_year1
    "12:30|15/11/2023-11:45|15/11/2023",    // invalidCondition3
    "12:30|32/11/2023-16:45|15/11/0000",    // invalid_both => result invalid datetime1 only
    "ab:30|15/11/2023-16:45|15/11/2023"     // invalid input but requirement say nothing about this case, and I let hh==-1101 to show it can lead to result -1 like it is valid
};

char testcase_requirement6_editCommands[][7] = {
    "Edit #1 title:[Valid Task Title]",
    "Edit #2 description:[Valid Task Description]",
    "Edit #3 time:[Valid Task Time]",
    "Edit #4 title:[Invalid, lack of end bracket, out_title still null, be careful to print",
    "Edit #5 description:[Invalid, lack of end bracket, out_description still null, be careful to print",
    "Edit #6 time:[T]ask Time] Valid cuz requirement say nothing about exceed characters behind closing bracket",
    "Edit #7 title:[Valid Task Title with length > MAX_SIZE_TITLE and copy only first 99 character, 1 for null-terminated-------end]"};

char testcase_requirement7_editCommands[][3] = {
    "Edit #1 explain:[1, valid]",
    "Edit 12 explain:[-1, no num component, lack of #]",
    "Edit #-10 explain:[0, invalid cuz negative]",
};

char testcase_requirement8_editCommands[][11] = {
    "Edit #1 title:[1, valid]",
    "Edit #2 description:[2, valid]",
    "Edit #3 time:[3, valid]",
    "Edit #4 status:[4, valid]",
    "Edit #5 invalid type:[5, invalid]",
    "Edit  title:[1, valid cuz requirement say nothing about lack of num case]",
    "   title:[0, invalid cuz there will be 1 whitespace before title after extracted field]",
    "  :title:[0, invalid cuz there will be null for field after extracted]",
    "Edit #9[abcd title: 1, valid cuz requirement say notthing about invalid num]",
    "Edit#10  title:[1, valid cuz requirement say nothing about invalid num component location]",
    " #11 title:[1, valid cuz requirement say nothing about lack of Edit]"};

char testcase_requirement9_editCommands[][4] = {
    "Edit #1 status:[I]",
    "Edit #2 status:[d]",
    "Edit #3 status:[A]",
    "Edit #4 status:[InvalidStatus, only 1 character]"};

char testcase_requirement17_tasksToAdd[][4][3] = {
    {"Title 1", "Description 1", "07:00|01/10/2023-12:00|01/10/2023"},
    {"Title 2 with length >= MAX_SIZE_TITLE to test buffer---------------100char-----------------------end"
    , "Description 2"
    , "07:00|01/10/2023-12:00|01/10/2023"},
    {"Title 2 with length < MAX_SIZE_TITLE to test buffer----------------99char-----------------------end"
    , "Description 3"
    , "07:00|01/10/2023-12:00|01/10/2023"},
    {"Title 4", "Description 4", "07:00|01/10/2023-12:00|01/10/2023"}};

char testcase_requirement18_tasksToDelete[][4][3] = {
    "Title 1", "Description 1", "07:00|01/10/2023-12:00|01/10/2023",
    "Title 2", "Description 2", "07:00|01/10/2023-12:00|01/10/2023",
    "Title 3", "Description 3", "07:00|01/10/2023-12:00|01/10/2023",
    "Title 4", "Description 4", "07:00|01/10/2023-12:00|01/10/2023"};

char normal_addCommands[][30][3] = {
    {"Add", "[Title 1]", "[Description 1]", "[07:00|01/10/2023-12:00|01/10/2023]"},
    {"Add", "[Title 2]", "[Description 2]", "[08:00|01/10/2023-13:00|01/10/2023]"},
    {"Add", "[Title 3]", "[Description 3]", "[10:00|01/10/2023-15:00|01/10/2023]"},
    {"Add", "[Title 4]", "[Description 4]", "[12:00|04/10/2023-17:00|05/10/2023]"},
    {"Add", "[Title 5]", "[Description 5]", "[14:00|03/10/2023-19:00|03/10/2023]"},
    {"Add", "[Title 6]", "[Description 6]", "[16:00|01/10/2023-21:00|01/10/2023]"},
    {"Add", "[Title 7]", "[Description 7]", "[18:00|01/10/2023-23:00|01/10/2023]"},
    {"Add", "[Title 8]", "[Description 8]", "[20:00|01/10/2023-01:00|02/10/2023]"},
    {"Add", "[Title 9]", "[Description 9]", "[22:45|01/10/2023-03:45|02/10/2023]"},
    {"Add", "[Title 10]", "[Description 10]", "[23:59|01/10/2023-04:59|02/10/2023]"},
    // Next week
    {"Add", "[Title 11]", "[Description 11]", "[07:00|08/10/2023-12:00|08/10/2023]"},
    {"Add", "[Title 12]", "[Description 12]", "[08:30|08/10/2023-13:30|08/10/2023]"},
    {"Add", "[Title 13]", "[Description 13]", "[10:15|08/10/2023-15:15|08/10/2023]"},
    {"Add", "[Title 14]", "[Description 14]", "[12:45|08/10/2023-17:45|08/10/2023]"},
    {"Add", "[Title 15]", "[Description 15]", "[14:30|08/10/2023-19:30|08/10/2023]"},
    {"Add", "[Title 16]", "[Description 16]", "[16:00|08/10/2023-21:00|08/10/2023]"},
    {"Add", "[Title 17]", "[Description 17]", "[18:15|08/10/2023-23:15|08/10/2023]"},
    {"Add", "[Title 18]", "[Description 18]", "[20:30|08/10/2023-01:30|09/10/2023]"},
    {"Add", "[Title 19]", "[Description 19]", "[22:45|08/10/2023-03:45|09/10/2023]"},
    {"Add", "[Title 20]", "[Description 20]", "[23:59|08/10/2023-04:59|09/10/2023]"},
    // Previous week
    {"Add", "[Title 21]", "[Description 21]", "[07:00|24/09/2023-12:00|24/09/2023]"},
    {"Add", "[Title 22]", "[Description 22]", "[08:30|24/09/2023-13:30|24/09/2023]"},
    {"Add", "[Title 23]", "[Description 23]", "[10:15|24/09/2023-15:15|24/09/2023]"},
    {"Add", "[Title 24]", "[Description 24]", "[12:45|24/09/2023-17:45|24/09/2023]"},
    {"Add", "[Title 25]", "[Description 25]", "[14:30|24/09/2023-19:30|24/09/2023]"},
    {"Add", "[Title 26]", "[Description 26]", "[16:00|24/09/2023-21:00|24/09/2023]"},
    {"Add", "[Title 27]", "[Description 27]", "[18:15|24/09/2023-23:15|24/09/2023]"},
    {"Add", "[Title 28]", "[Description 28]", "[20:30|24/09/2023-01:30|25/09/2023]"},
    {"Add", "[Title 29]", "[Description 29]", "[22:45|24/09/2023-03:45|25/09/2023]"},
    {"Add", "[Title 30]", "[Description 30]", "[23:59|24/09/2023-04:59|25/09/2023]"}};

char normal_editCommands[][4] = {
    "Edit #1 status:[A]",
    "Edit #2 title:[Changed title]",
    "Edit #3 description:[Changed description]",
    "Edit #4 time:[23:59|24/09/2023-04:59|25/09/2023]"};

char normal_deleteCommands[][3] = {
    "Delete #1",
    "Delete #2",
    "Delete #3",
    "Delete #0",
    "Delete #-1",
    "Delete #200"};

char normal_showCommands[][10] = {
    "Show #5",
    "Show all",
    "Show head %2",
    "Show tail %3",
    "Show filter title:[1]",
    "Show filter description:[Des]",
    "Show filter status:[A]",
    "Show week time:[01/10/2023],"
};

char normal_quitCommands[] = "Quit";
















