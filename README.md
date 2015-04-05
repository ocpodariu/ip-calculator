#IP Calculator

Network subnetting utility primarily designed to help students better understand and verify their knowledge about the process of subnetting. It also supports __`VLSM`__ to allow for a more efficient address space usage.

## Features
* Identify the type of an IP address (network / broadcast / host)
* Subnet a larger network into multiple smaller ones

## Usage Example
#### Scenario
You have been asked to design a network addressing scheme for your company's intranetwork, that will allow an 80% growth in all departments.
The original network address is: `116.40.0.0 /16`
![Intranetwork](https://cloud.githubusercontent.com/assets/5685993/6997682/5472cf10-dbce-11e4-8317-4af86c92dc2e.png)

#### Determine number of necessary host IPs
The first step is to determine how many subnetworks the intranetwork has, and the corresponding number of necessary host IPs for each of them.

| # | Subnet                               | Host IPs  | Host IPs + 80%  | Comment |
|---|:------------------------------------:|----------:|----------------:|---------|
| 1 | Research                             | 140       | 252             | -       |
| 2 | Deployment                           |  57       | 103             | -       |
| 3 | Marketing + Administration + Sales   | 411       | 739             | They are grouped because they connect through the same router interface. |
| 4 | RouterA - RouterB                    |   2       |   2             | No need to add 80% growth as this is a point-to-point link and it always needs only 2 IPs. |

#### Create input file
__CAUTION!__
To work correctly, the subnet process must first order the subnetworks descendingly by the number of necessary host IPs. Therefore, the order of the subnetworks in the output file is not the same as in the input file.
To avoid any confusion and possible mistakes, enter the list of host IPs necessary for each subnetwork, already sorted.

Create the input file `subnet.txt`:
```
116.40.0.0  <- original network
255.255.0.0

4    <- number of subnetworks

739  <- host IPs necessary for subnetwork #3
252  <- host IPs necessary for subnetwork #1
103  <- host IPs necessary for subnetwork #2
2    <- host IPs necessary for subnetwork #4
```

#### Subnet
Enter the `subnet` command and choose file input and output:
![Subnet](https://cloud.githubusercontent.com/assets/5685993/6997684/64eb98cc-dbce-11e4-81b0-ca28f0ec0625.png)

#### Check results
Open the output file, `subnet_out.txt`, and view the results:
![Check results](https://cloud.githubusercontent.com/assets/5685993/6997685/64ef7186-dbce-11e4-9d85-952a78994f8d.png)

_The input and output files corresponding to this scenario can be found at "examples/subnet.txt" and "output/subnet_out.txt" respectively._