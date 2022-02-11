# CSE306PRE1
Description
NAME
csv - process data in a CSV (Comma-Separated Value) file.
SYNOPSIS
**csv [-frh] [-max field] [-min field] [-mean field] [-records field value] file**
DESCRIPTION
The csv program reads data from a CSV file (file), processes the contents and produces results according to command-line arguments, as follows.

**-f** Display the number of fields in the first record of file.

**-r** Display the number of data records in file. If -h is not given this is the number of lines in the file. If -h is given this is one less than the number of lines in the file.

**-h** Treat the first record of file as a header record rather than a data record. If this option is used then field in the followins options must be specified with the title of the corresponding field from the header row (the numeric positional option is not available).

**-max field** Display the maximum value in the indicated field of the data records. The first field is numbered 0. This option ignores non-numeric data in the indicated field. If there is no numeric data in the indicated field in any of the data records the program exits with error code EXIT_FAILURE. See how fields are identified when the -h option is used.

**-min field** Display the minimum value in the indicated field of the data records. The first field is numbered 0. This option ignores non-numeric data in the indicated field. If there is no numeric data in the indicated field in any of the data records the program exits with error code EXIT_FAILURE. See how fields are identified when the -h option is used.

**-mean field** Display the arithmetic mean (average) value in the indicated field of the data records. The first field is numbered 0. This option ignores non-numeric data in the indicated field. If there is no numeric data in the indicated field in any of the data records the program exits with error code EXIT_FAILURE. See how fields are identified when the -h option is used.

**-records field** value Display the records from file containing value in the the indicated field. The first field is numbered 0. Value is formatted according to the same rules as data in fields. See how fields are identified when the -h option is used.
