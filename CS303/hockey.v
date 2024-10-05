module hockey(

    input clk,
    input rst,

    input BTNA,
    input BTNB,

    input [1:0] DIRA,
    input [1:0] DIRB,

    input [2:0] YA,
    input [2:0] YB,

    output reg LEDA,
    output reg LEDB,
    output reg [4:0] LEDX,

    output reg [6:0] SSD7,
    output reg [6:0] SSD6,
    output reg [6:0] SSD5,
    output reg [6:0] SSD4,
    output reg [6:0] SSD3,
    output reg [6:0] SSD2,
    output reg [6:0] SSD1,
    output reg [6:0] SSD0
  );

  //parameter selectSec = 1; // 1 second period or 0.5 for half a second period (assuming clk is 100HZ)
  reg [2:0] sizeOfField = 5; //Changeble from 4 to 7 (sizeOfField = 5 for 5x5)
  reg [2:0] winningScore = 3; //Changeable from 1 to 7
  reg [7:0] timeScale = 100; // 50 for 2/s or 100 for 1/s
  // ^^^^ Make up lab ^^^^
  

  reg [0:0] turn = 1'b0;
  reg [2:0] scoreA = 2'b00;
  reg [2:0] scoreB = 2'b00;
  reg [6:0] timer = 2'b00;


  reg [3:0] IDLE = 4'b0000;
  reg [3:0] DISP = 4'b0001;
  reg [3:0] HIT_A = 4'b0010;
  reg [3:0] HIT_B = 4'b0011;
  reg [3:0] SEND_A = 4'b0100;
  reg [3:0] SEND_B = 4'b0101;
  reg [3:0] RESP_A = 4'b0110;
  reg [3:0] RESP_B = 4'b0111;
  reg [3:0] GOAL_A = 4'b1000;
  reg [3:0] GOAL_B = 4'b1001;
  reg [3:0] WIN = 4'b1010;

  reg [3:0] cState = 4'b0000;
  reg [1:0] dirY = 2'b00;

  reg [7:0] val0 = 7'b0000001;
  reg [7:0] val1 = 7'b1001111;
  reg [7:0] val2 = 7'b0010010;
  reg [7:0] val3 = 7'b0000110;
  reg [7:0] val4 = 7'b1001100;
  reg [7:0] val5 = 7'b0100100;
  reg [7:0] val6 = 7'b0100000;
  reg [7:0] val7 = 7'b0001111;
  reg [7:0] vala = 7'b0001000;
  reg [7:0] valb = 7'b1100000;
  reg [7:0] valEmpty  =  7'b1111111;
  reg [7:0] valInvalid = 7'b1111110;
  reg [2:0] Y_COORD ;
  reg [2:0] X_COORD ;

  // you may use additional always blocks or drive SSDs and LEDs in one always block
  // for state machine and memory elements
  always @(posedge clk or posedge rst)
  begin
    if (rst)
    begin
      timer <= 0;
      scoreA <= 0;
      scoreB <= 0;
      cState <= IDLE;
      
    end
    else begin
      
        
      case (cState)
        IDLE:
        begin
          if(BTNA == 1'b1 && BTNB == 1'b0)
          begin // A's turn
            turn <= 1'b0;
            cState <= DISP;
          end
          else if(BTNA == 1'b0 && BTNB == 1'b1)
          begin // B's turn
            turn <= 1'b1;
            cState <= DISP;
          end
          else
          begin
            cState <= IDLE;
          end
        end

        DISP:
        begin
          if (timer < timeScale)
          begin
            timer <= timer + 1;
            cState <= DISP;
          end
          else
          begin
            timer <= 0;
            if(turn == 1)
            begin
              cState <= HIT_B;
            end
            else if(turn == 0)
            begin
              cState <= HIT_A;

            end
          end
        end

        HIT_A:
        begin
          
          if(BTNA == 1'b1 && YA < (sizeOfField) && DIRA !=3)
          begin 
            X_COORD <= 3'b000;
            Y_COORD <= YA;
            dirY <= DIRA;

            cState <= SEND_B; //Sent to B
          end
          else
          begin
            cState <= HIT_A;
          end
        end

        HIT_B:
        begin
          
          if(BTNB == 1'b1 && YB < sizeOfField && DIRB != 3)
          begin  
            X_COORD <= (sizeOfField-1);
            Y_COORD <= YB;
            dirY <= DIRB;
            cState <= SEND_A; //Sent to A
          end
          else
          begin
            cState <= HIT_B;
          end
        end

        SEND_A:
        begin
          if (timer < timeScale)
          begin
            timer <= timer + 1;
            cState <= SEND_A;
          end
          else
          begin
            timer <= 0;
            if(dirY == 2'b00 || dirY == 2'b11)
            begin
              Y_COORD <= Y_COORD;
            end
            else if(dirY == 2'b10 && ~(Y_COORD == 0) ||   Y_COORD == (sizeOfField-1))
            begin
              dirY <= 2'b10;
              Y_COORD <= Y_COORD - 1;
            end
            else
            begin
              dirY <= 2'b01;
              Y_COORD <= Y_COORD + 1;
            end

            if(X_COORD > 1)
            begin
              X_COORD <= X_COORD - 1;
              cState <= SEND_A;
            end
            else
            begin
              X_COORD <= 0;
              cState <= RESP_A;
            end
          end
        end

        SEND_B:
        begin
          if (timer < timeScale)
          begin
            timer <= timer + 1;
            cState <= SEND_B;
          end
          else
          begin
            timer <= 0;
            if(dirY == 2'b00 || dirY == 2'b11)
            begin
              Y_COORD <= Y_COORD;
            end
            else if(dirY == 2'b10 && ~(Y_COORD == 0) ||   Y_COORD == (sizeOfField-1))
            begin
              dirY <= 2'b10;
              Y_COORD <= Y_COORD - 1;
            end
            else
            begin
              dirY <= 2'b01;
              Y_COORD <= Y_COORD + 1;
            end

            if(X_COORD < (sizeOfField-2))
            begin
              X_COORD <= X_COORD + 1;
              cState <= SEND_B;
            end
            else
            begin
              X_COORD <= (sizeOfField-1); 
              cState <= RESP_B;
            end
          end
        end

        RESP_A:
        begin
          if (timer < timeScale)
          begin
            if(BTNA == 1 && Y_COORD == YA && DIRA != 3)
            begin
              X_COORD <= 1;
              timer <= 0;
              cState <= SEND_B;
              if(DIRB == 2'b00)
              begin
                dirY <= DIRB;
              end
              else if(DIRA == 2'b10 && ~(YA == 0) ||   YA == (sizeOfField-1))
              begin
                dirY <= 2'b10;
                Y_COORD <= Y_COORD - 1;
              end
              else
              begin
                dirY <= 2'b01;
                Y_COORD <= Y_COORD + 1;
              end
            end
            else
            begin
              timer <= timer + 1;
              cState <= RESP_A;
            end
          end
          else
          begin
            scoreB <= scoreB + 1;
            timer<=0;
            cState <= GOAL_B;
          end
        end

        RESP_B:
        begin
          if(timer < timeScale)
          begin
            if(BTNB == 1 && Y_COORD == YB && DIRB !=3)
            begin
              X_COORD <= (sizeOfField-2); 
              timer <= 0;
              cState <= SEND_A;

              if(DIRB == 2'b00)
              begin
                dirY <= DIRB;
              end
              else if(DIRB == 2'b10 && ~(YB == 0) ||   YB == (sizeOfField-1))
              begin
                dirY <= 2'b10;
                Y_COORD <= Y_COORD - 1;
              end
              else
              begin
                dirY <= 2'b01;
                Y_COORD <= Y_COORD + 1;
              end
            end
            else
            begin
              timer <= timer + 1;
              cState <= RESP_B;
            end
          end
          else
          begin
            timer <= 0;
            scoreA <= scoreA + 1;
            cState <= GOAL_A;
          end
        end

        GOAL_A:
        begin
          
          if(timer < timeScale)
          begin
            timer <= timer + 1;
            cState <= GOAL_A;
          end
          else
          begin
            timer <= 0;
            if(scoreA == winningScore)
            begin
              turn <= 1'b0;
              cState <= WIN;
            end
            else
            begin
              cState <= HIT_B;
            end
          end
        end

        GOAL_B:
        begin
        
          if(timer < timeScale)
          begin
            timer <= timer + 1;
            cState <= GOAL_B;
          end
          else
          begin
            timer <= 0;
            if(scoreB == winningScore)
            begin
              turn <= 1'b1;
              cState <= WIN;
            end
            else
            begin
              cState <= HIT_A;
            end
          end
        end


        WIN:
        begin
          if(timer < 50)
          begin
          timer <= timer+1;
          end
          else begin
           turn<=~turn;
           timer<=0;
          end

          //LED'S WILL BLINK WITH 1 SECOND PERIOD
          cState <= cState;
        end
      endcase
    end
  end

  // for SSDs
  always@(*)
  begin
    SSD3 = valEmpty;
    SSD5 = valEmpty;
    SSD6 = valEmpty;
    SSD7 = valEmpty;
    if(cState == SEND_A || cState == SEND_B || cState == RESP_A || cState == RESP_B)
    begin
      case (Y_COORD) //SSD4w: number
        0:
        begin
          SSD4=val0;
        end
        1:
        begin
          SSD4=val1;
        end
        2:
        begin
          SSD4=val2;
        end
        3:
        begin
          SSD4=val3;
        end
        4:
        begin
          SSD4=val4;
        end
        5:
        begin
          SSD4=val5;
        end
        6:
        begin
          SSD4=val6;
        end
        default:
        begin
          SSD4= valEmpty;
        end
      endcase
    end
    else if(cstate == HIT_A)
    begin
      case (YA) //SSD4w: number
        0:
        begin
          SSD4=val0;
        end
        1:
        begin
          SSD4=val1;
        end
        2:
        begin
          SSD4=val2;
        end
        3:
        begin
          SSD4=val3;
        end
        4:
        begin
          SSD4=val4;
        end
        5:
        begin
          SSD4=val5;
        end
        6:
        begin
          SSD4=val6;
        end
        default:
        begin
          SSD4= valEmpty;
        end
      endcase
    end
    else if(cstate == HIT_B)
    begin
      case (YB) //SSD4w: number
        0:
        begin
          SSD4=val0;
        end
        1:
        begin
          SSD4=val1;
        end
        2:
        begin
          SSD4=val2;
        end
        3:
        begin
          SSD4=val3;
        end
        4:
        begin
          SSD4=val4;
        end
        5:
        begin
          SSD4=val5;
        end
        6:
        begin
          SSD4=val6;
        end
        default:
        begin
          SSD4= valEmpty;
        end
      endcase
    end
    else if(cState == WIN)
    begin
      if(scoreB == 2'b11)
      begin
        //B WON
        SSD4= valb; //b
      end
      else
      begin
        //A WON
        SSD4= vala; //A
      end
    end
    else
    begin
      SSD4 = valEmpty;
    end
    
    if(cState == IDLE)
    begin
      SSD2 = vala;        //A
      SSD1 = valInvalid;  //-
      SSD0 = valb;        //b
    end
    else if(cState == DISP || cState == GOAL_A || cState == GOAL_B || cState == WIN)
    begin
      case(scoreA)
        0:
        begin
          SSD2=val0;
        end
        1:
        begin
          SSD2=val1;
        end
        2:
        begin
          SSD2=val2;
        end
        3:
        begin
          SSD2=val3;
        end
        4:
        begin
          SSD2=val4;
        end
        5:
        begin
          SSD2=val5;
        end
        6:
        begin
          SSD2=val6;
        end
        7:
        begin
          SSD2=val7;
        end
        default:
        begin
          SSD2=valEmpty;
        end
      endcase

      case(scoreB)
        0:
        begin
          SSD0=val0;
        end
        1:
        begin
          SSD0=val1;
        end
        2:
        begin
          SSD0=val2;
        end
        3:
        begin
          SSD0=val3;
        end
        4:
        begin
          SSD0=val4;
        end
        5:
        begin
          SSD0=val5;
        end
        6:
        begin
          SSD0=val6;
        end
        7:
        begin
          SSD0=val7;
        end
        default:
        begin
          SSD0=valEmpty;
        end
      endcase
      SSD1 = 7'b1111110;
    end     
    else begin
      SSD0 = valEmpty;
      SSD1 = valEmpty;
      SSD2 = valEmpty;
    end
  end

  //for LEDs
  always @ (*)
  begin
    if(cState == SEND_A || cState == SEND_B || cState == RESP_A || cState == RESP_B)
    begin
      case (X_COORD)
        0:
        begin
          LEDX=5'b10000;
        end
        1:
        begin
          LEDX=5'b01000;
        end
        2:
        begin
          LEDX=5'b00100;
        end
        3:
        begin
          LEDX=5'b00010;
        end
        4:
        begin
          LEDX=5'b00001;
        end
        default:
        begin
          LEDX=5'b00000;
        end
      endcase
    end
    else if(cState == WIN)
    begin
      LEDX= turn? 5'b10101 : 5'b01010;
    end
    else
    begin
      LEDX= 5'b00000;
    end

    if(cState == HIT_A || cState == RESP_A || cState == IDLE)
    begin
      LEDA = 1;
    end
    else
    begin
      LEDA = 0;
    end

    if(cState == HIT_B || cState == RESP_B || cState == IDLE)
    begin
      LEDB = 1;
    end
    else
    begin
      LEDB = 0;
    end
  end


endmodule
