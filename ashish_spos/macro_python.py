# # # Pass-I: Define data structures
# # MNT = {}  # Macro Name Table (holds macro names and their index in MDT)
# # MDT = []  # Macro Definition Table (holds macro instructions)
# # intermediate_code = []  # Stores code without macro definitions

# # def pass1(source_code):
# #     # Variables for tracking macros
# #     inside_macro = False
# #     macro_name = ""
    
# #     # Process each line of the source code
# #     for line in source_code:
# #         words = line.strip().split()  # Split the line into words
        
# #         # Start of a macro definition
# #         if words[0] == "MACRO":
# #             inside_macro = True
# #             continue  # Skip this line and go to the next

# #         # If inside macro definition, add to MDT
# #         if inside_macro:
# #             if words[0] not in MNT:
# #                 macro_name = words[0]  # Macro name
# #                 MNT[macro_name] = len(MDT)  # Store macro name and MDT index in MNT
# #             MDT.append(" ".join(words))  # Add definition to MDT
# #             if words[0] == "MEND":  # End of macro definition
# #                 inside_macro = False
# #             continue  # Continue processing the next line
            
# #         # If not inside a macro, add to intermediate code
# #         intermediate_code.append(line)

# # def pass2(intermediate_code):
# #     output_code = []  # Final expanded code after processing macros
    
# #     # Process each line in the intermediate code
# #     for line in intermediate_code:
# #         words = line.strip().split()  # Split the line into words
        
# #         # Check if the first word is a macro call
# #         if words[0] in MNT:
# #             macro_start = MNT[words[0]]  # MDT index from MNT
# #             # Copy macro instructions from MDT to output code
# #             for i in range(macro_start, len(MDT)):
# #                 if MDT[i] == "MEND":  # End of macro definition
# #                     break
# #                 output_code.append(MDT[i])
# #         else:
# #             output_code.append(line)  # Regular instruction, add to output as-is
    
# #     return output_code

# # # Input code with a simple macro definition
# # source_code = [
# #     "MACRO",
# #     "INCR &ARG",
# #     "LDA &ARG",
# #     "ADD =1",
# #     "STA &ARG",
# #     "MEND",
# #     "START",
# #     "INCR X",  # Macro call
# #     "INCR Y",  # Another macro call
# #     "END"
# # ]

# # # Execute Pass-I
# # pass1(source_code)

# # # Display results of Pass-I
# # print("\nMNT:", MNT)
# # print("\nMDT:", MDT)
# # print("\nIntermediate Code:", intermediate_code)

# # # Execute Pass-II
# # final_code = pass2(intermediate_code)

# # # Display final output code after macro expansion
# # print("\nFinal Output Code after Pass-II:")
# # for line in final_code:
# #     print(line)




MNT={}
MDT=[]
intermediate_code=[]

def pass1(source_code):
	inside_macro=False
	macro_name=""
	
	for line in source_code:
		words=line.strip().split()

		if words[0]=="MACRO":
			inside_macro=True
			continue

		if inside_macro:
			if words[0] not in MNT:
				macro_name=words[0]
				MNT[macro_name]=len(MDT)
			MDT.append(" ".join(words))
			if words[0] =="MEND":
				inside_macro=False
				continue

		intermediate_code.append(line)

def pass2(intermediate_code):
	output_code=[]

	for line in intermediate_code:
		words=line.strip().split()
		
		if words[0] in MNT:
			macro_start=MNT[words[0]]
			
			for i in range(macro_start,len(MDT)):
				if MDT[i]=="MEND":
					break
				output_code.append(MDT[i])
		else:
			output_code.append(line)

	return output_code

source_code=[
	"MACRO",
	"INCR &ARG",
	"LDA &ARG",
	"ADD =1",
	"STA &ARG",
	"MEND",
	"START",
	"INCR X",
	"INCR y",
	"END"
]	

pass1(source_code)

print("\nMNT:",MNT)
print("\nMDT:",MDT)
print("\nintermediate code:",intermediate_code)

final_code=pass2(intermediate_code)

print("\nfinal output code after pass2:")

for line in final_code:
	print(line)

