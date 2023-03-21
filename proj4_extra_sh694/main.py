from extra import query1, query2, query3, query4, query5


C = f"postgresql://postgres:passw0rd@localhost/ACC_BBALL"
# Example usage of query1
query1(C, use_mpg=True, min_mpg=35, max_mpg=40,
       use_ppg=False, min_ppg=10, max_ppg=20,
       use_rpg=False, min_rpg=5, max_rpg=10,
       use_apg=False, min_apg=3, max_apg=8,
       use_spg=False, min_spg=1, max_spg=3,
       use_bpg=False, min_bpg=0.5, max_bpg=1.5)

# Example usage of query2
query2(C, 'Red')

# Example usage of query3
query3(C, 'Duke')

# Example usage of query4
query4(C, 'NC', 'Red')

# Example usage of query5
query5(C, 13)

if __name__ == '__main__':
    pass