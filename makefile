OBJS = Top_main.o Lp_main.o Add_var.o Add_obj.o Add_st.o

Top_main : $(OBJS)
	gcc $^ -o Top_main -lglpk -lm

Lp_main.o : Lp_main.c  lp_var.h glpk_var.h
	gcc -c $< -o $@
Add_var.o : Add_var.c  lp_var.h glpk_var.h
	gcc -c $< -o $@
Add_obj.o : Add_obj.c lp_var.h glpk_var.h
	gcc -c $< -o $@
Add_st.o : Add_st.c lp_var.h glpk_var.h
	gcc -c $< -o $@


clean:
	rm *.o 

