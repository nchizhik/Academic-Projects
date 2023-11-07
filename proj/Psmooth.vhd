library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_textio.all;
use std.textio.all;

package Psmooth is	
function smooth(data: std_logic_vector)	return std_logic_vector;
end package Psmooth;

package body Psmooth is	
	function smooth(data: std_logic_vector) return std_logic_vector is
		variable tmp: std_logic_vector(44 downto 0);
		variable min: std_logic_vector(4 downto 0):= tmp(44 downto 40);
		variable max: std_logic_vector(4 downto 0):= tmp(44 downto 40);
		variable center: std_logic_vector(4 downto 0):= tmp(24 downto 20); --Center pixel
	begin
	
	tmp:= data;
	
	for i in 0 to 3 loop 
	if (tempRow(44-(i*5) downto 40-(i*5)) < min) then
	min:=tempRow(44-(i*5) downto 40-(i*5));
	
	elsif (tempRow(44-(i*5) downto 40-(i*5))> max) then
	max:=tempRow(44-(i*5) downto 40-(i*5));
	
	elsif (tempRow(19-(i*5) downto 15-(i*5))< min) then
	min:=tempRow(19-(i*5) downto 15-(i*5));
	
	elsif (tempRow(19-(i*5) downto 15-(i*5))> max) then
	max:=tempRow(19-(i*5) downto 15-(i*5));	
		
	end if;
	end loop;
	
	if (center< min) then center :=min;
	elsif (center< max) then center:=max;
	end if;
	
	tmp(24 downto 20):= center;
	
	return tmp(24 downto 20); -- Return the center pixel
	end function smooth;
	end package body Psmooth;
	