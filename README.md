# Importance-sampling
## Cpp
### find_trap
To find cycle containing common k VN
Input: 
1.Code length: L
2.The number of common VNs : k

Output: 
1.write (? cycle common k VN.txt)
2.write (? cycle common k VN within many cycles.txt)  //harmful trapping sets

### find_VN_cycle_idex
To find cycle of VN bit
Input: 
1.Code length: L

Output: 
1.write (? cycle idex sorting)  //sort cycle idex
2.wirte (? cycle bit)           //cycle of VN bit

## C
### IS_cycle_avg
Do IS by biasing all cycle to decode and doing average number of cycle 

## txt
### 6 cycle idex.txt
Number of cycle, number of VN in cycle 6
Every row represent the cycle of VN idex...
### 6 cycle bit.txt
Number of cycle, number of VN in cycle 6
i row represent cycle idex relating to VN i

### 6 cycle common 2 VN.txt
Number of cycle common two VNs within two cycles
Every row is the cycle idex of common two VNs

### 6 cycle common 2 VN within many cycles.txt
Number of cycle common two VNs within many cycles
Every row is the cycle idex of common two VNs

### 8 cycle common 3 VN.txt
Number of cycle common two VNs within two cycles
Every row is the cycle idex of common two VNs

### 8 cycle common 3 VN within many cycles.txt
Number of cycle common three VNs within many cycles
Every row is the cycle idex of common three VNs
