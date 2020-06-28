
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use work.nn_package.all;

entity n_hidden is
    Port ( 
        clk : in std_logic;
        x, w : in x_array;
        bi : in signed(N-1 downto 0);
        sum_out : out signed(N-1 downto 0));
end n_hidden;

 
    
    
architecture Behavioral of n_hidden is

component mult 
         Port ( a : in SIGNED (N-1 downto 0);
           b : in SIGNED (N-1 downto 0);
           c : out SIGNED (N-1 downto 0));
    end component;
    
 component summer1 
       Port(  mult_array2 : in x_array;
           result : out SIGNED (N-1 downto 0));
    end component;
    
    signal mult_array : x_array;
    signal sum, cum_sum1 : signed(N-1 downto 0);

begin

    -- Multiply each input with its corresponding weight
    -- YOUR CODE HERE
    mult0:  for i in 0 to NUM_X-1 generate
   begin
   ct: mult
   port map(a => x(i),  b => w(i), c => mult_array(i));
   end generate;
	-----------------
	-----------------
	-----------------
    
     --Sum the products and bias
    
   
   ct: summer1
   port map( mult_array2 => mult_array, result => cum_sum1);

sum_out <= cum_sum1 + bi;
    -- YOUR CODE HERE
	-----------------
	-----------------
	-----------------
    
  

end Behavioral;
