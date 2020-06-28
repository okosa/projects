library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use work.nn_package.all;

entity nn_tb is
--    Port ( );
end nn_tb;

architecture Behavioral of nn_tb is

component nn is
    Port (  clk : in std_logic;
        x_in : in x_array;
        y_out : out y_array);
end component;

constant time_delta : time := 10ns;
constant CLR_delta : time := 20ns;
signal CLK : STD_LOGIC;
signal x_in : x_array;
signal y_out: y_array;

begin
    
ct : nn port map ( clk => CLK, x_in => x_in, y_out => y_out);

    process
    begin
        CLK <= '0';
        wait for time_delta;
        CLK <= '1';
        wait for time_delta;
    end process;
    
    process
    begin
        x_in<= ("00000000000000000110110000100101","00000000000000000101111010011000",  "00000000000000000000000000110000",  "00000000000000000110110010100010",  "00000000000000000101111001101111",  "00000000000000000000000000110001");     
        
        wait for CLR_delta;
    end process;
         
end Behavioral;
