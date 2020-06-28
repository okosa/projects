library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use work.nn_package.all;

entity summer is
port(
           mult_array2 : a_array;
           result : out SIGNED (N-1 downto 0));
end summer;

architecture Behavioral of summer is
signal result1: SIGNED (N-1 downto 0);
begin
result <= "00000000000000000000000000000000";
add:  for i in 0 to NUM_X-1 generate
   begin
result1 <= mult_array2(i) + result1 ;
end generate;
end Behavioral;
