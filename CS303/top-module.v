`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 01/05/2023 05:35:09 PM
// Design Name:
// Module Name: top_module
// Project Name:
// Target Devices:
// Tool Versions:
// Description:
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////


module top_module(
    input clk,

    input rst,

    input BTNA,

    input BTNB,

    input [1:0] DIRA,

    input [1:0] DIRB,

    input [2:0] YA,

    input [2:0] YB,

    output LEDA,

    output LEDB,

    output [4:0] LEDX,

    output a_out,b_out,c_out,d_out,e_out,f_out,g_out,p_out,
    output [7:0]an
  );
  wire newclk , dBTNA ,dBTNB;
  wire [6:0] SSD0 ,SSD1 ,SSD2 , SSD3 ,SSD4, SSD5, SSD6, SSD7;
  clk_divider c ( .clk_in(clk), .rst(rst), .divided_clk(newclk));
  ssd s (.clk(clk),.rst(rst),
        .SSD7(SSD7) , .SSD6(SSD6) , .SSD5(SSD5) , .SSD4(SSD4) , 
        .SSD3(SSD3) , .SSD2(SSD2) , .SSD1(SSD1) , .SSD0(SSD0) , 
        .a_out(a_out), .b_out(b_out), .c_out(c_out), .d_out(d_out),
        .e_out(e_out), .f_out(f_out), .g_out(g_out), .p_out(p_out),
        .an(an)
      );

  hockey h (.clk(newclk), .rst(rst),
            .BTNA(dBTNA), .BTNB(dBTNB),
            .DIRA(DIRA), .DIRB(DIRB),
            .YA(YA), .YB(YB),
            .LEDA(LEDA), .LEDB(LEDB), .LEDX(LEDX),
            .SSD7(SSD7) , .SSD6(SSD6) , .SSD5(SSD5) , .SSD4(SSD4) , 
            .SSD3(SSD3) , .SSD2(SSD2) , .SSD1(SSD1) , .SSD0(SSD0) 
           );
  debouncer btna (
            .clk(newclk), .rst(rst),
            .noisy_in(BTNA), .clean_out(dBTNA)
  );
  debouncer btnb (
            .clk(newclk), .rst(rst),
            .noisy_in(BTNB), .clean_out(dBTNB)
  );
endmodule
