/* This file was generated by SableCC (http://www.sablecc.org/). */

package de.tum.ascodt.sidlcompiler.frontend.lexer;


import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.PushbackReader;

import de.tum.ascodt.sidlcompiler.frontend.node.EOF;
import de.tum.ascodt.sidlcompiler.frontend.node.TArrayToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TAsToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TBlank;
import de.tum.ascodt.sidlcompiler.frontend.node.TBoolToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TClassToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TComma;
import de.tum.ascodt.sidlcompiler.frontend.node.TConstant;
import de.tum.ascodt.sidlcompiler.frontend.node.TDecimalConstant;
import de.tum.ascodt.sidlcompiler.frontend.node.TDocumentationComment;
import de.tum.ascodt.sidlcompiler.frontend.node.TDot;
import de.tum.ascodt.sidlcompiler.frontend.node.TDoubleToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TEndOfLineComment;
import de.tum.ascodt.sidlcompiler.frontend.node.TEnumToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TEquals;
import de.tum.ascodt.sidlcompiler.frontend.node.TExtendsToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TIdentifier;
import de.tum.ascodt.sidlcompiler.frontend.node.TImplementsToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TInToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TInoutToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TIntToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TInterfaceToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TLAngleBracket;
import de.tum.ascodt.sidlcompiler.frontend.node.TLBrace;
import de.tum.ascodt.sidlcompiler.frontend.node.TLBracket;
import de.tum.ascodt.sidlcompiler.frontend.node.TOpaqueToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TPackageToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TRAngleBracket;
import de.tum.ascodt.sidlcompiler.frontend.node.TRBrace;
import de.tum.ascodt.sidlcompiler.frontend.node.TRBracket;
import de.tum.ascodt.sidlcompiler.frontend.node.TSemicolon;
import de.tum.ascodt.sidlcompiler.frontend.node.TSignedDecimalNumber;
import de.tum.ascodt.sidlcompiler.frontend.node.TStringToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TTargetToken;
import de.tum.ascodt.sidlcompiler.frontend.node.TTraditionalComment;
import de.tum.ascodt.sidlcompiler.frontend.node.TUsesToken;
import de.tum.ascodt.sidlcompiler.frontend.node.Token;


@SuppressWarnings("nls")
public class Lexer {
  public static class State {
    public final static State INITIAL = new State(0);

    private int id;

    private State(@SuppressWarnings("hiding") int id) {
      this.id = id;
    }

    public int id() {
      return id;
    }
  }

  protected Token token;

  protected State state = State.INITIAL;
  private PushbackReader in;
  private int line;
  private int pos;
  private boolean cr;
  private boolean eof;

  private final StringBuffer text = new StringBuffer();

  private static int[][][][] gotoTable;
  /*
   * {
   * { // INITIAL
   * {{9, 9, 1}, {10, 10, 2}, {13, 13, 3}, {32, 32, 4}, {40, 40, 5}, {41, 41,
   * 6}, {44, 44, 7}, {45, 45, 8}, {46, 46, 9}, {47, 47, 10}, {48, 48, 11}, {49,
   * 57, 12}, {59, 59, 13}, {60, 60, 14}, {61, 61, 15}, {62, 62, 16}, {64, 64,
   * 17}, {65, 75, 18}, {76, 76, 19}, {77, 84, 18}, {85, 85, 20}, {86, 90, 18},
   * {91, 91, 21}, {95, 95, 18}, {97, 97, 22}, {98, 98, 23}, {99, 99, 24}, {100,
   * 100, 25}, {101, 101, 26}, {102, 104, 18}, {105, 105, 27}, {106, 107, 18},
   * {108, 108, 28}, {109, 110, 18}, {111, 111, 29}, {112, 112, 30}, {113, 114,
   * 18}, {115, 115, 31}, {116, 116, 18}, {117, 117, 32}, {118, 122, 18}, {123,
   * 123, 33}, {125, 125, 34}, },
   * {{9, 32, -2}, },
   * {{9, 32, -2}, },
   * {{9, 32, -2}, },
   * {{9, 32, -2}, },
   * {},
   * {},
   * {},
   * {{48, 57, 35}, },
   * {},
   * {{42, 42, 36}, {47, 47, 37}, },
   * {{48, 57, 11}, {76, 76, 38}, {85, 85, 39}, {108, 108, 40}, {117, 117, 41},
   * },
   * {{48, 57, 42}, {76, 117, -13}, },
   * {},
   * {},
   * {},
   * {},
   * {{116, 116, 43}, },
   * {{48, 57, 44}, {65, 90, 45}, {95, 95, 45}, {97, 122, 45}, },
   * {{48, 57, 44}, {65, 84, 45}, {85, 85, 46}, {86, 90, 45}, {95, 95, 45}, {97,
   * 116, 45}, {117, 117, 47}, {118, 122, 45}, },
   * {{48, 57, 44}, {65, 75, 45}, {76, 76, 48}, {77, 90, 45}, {95, 95, 45}, {97,
   * 107, 45}, {108, 108, 49}, {109, 122, 45}, },
   * {{93, 93, 50}, },
   * {{48, 95, -20}, {97, 114, 45}, {115, 115, 51}, {116, 122, 45}, },
   * {{48, 95, -20}, {97, 110, 45}, {111, 111, 52}, {112, 122, 45}, },
   * {{48, 95, -20}, {97, 107, 45}, {108, 108, 53}, {109, 122, 45}, },
   * {{48, 110, -25}, {111, 111, 54}, {112, 122, 45}, },
   * {{48, 95, -20}, {97, 109, 45}, {110, 110, 55}, {111, 119, 45}, {120, 120,
   * 56}, {121, 122, 45}, },
   * {{48, 95, -20}, {97, 108, 45}, {109, 109, 57}, {110, 110, 58}, {111, 122,
   * 45}, },
   * {{48, 122, -21}, },
   * {{48, 95, -20}, {97, 111, 45}, {112, 112, 59}, {113, 122, 45}, },
   * {{48, 95, -20}, {97, 97, 60}, {98, 122, 45}, },
   * {{48, 95, -20}, {97, 115, 45}, {116, 116, 61}, {117, 122, 45}, },
   * {{48, 108, -22}, {109, 114, 45}, {115, 115, 62}, {116, 122, 45}, },
   * {},
   * {},
   * {{48, 57, 35}, },
   * {{0, 41, 63}, {42, 42, 64}, {43, 127, 63}, },
   * {{0, 9, 65}, {10, 10, 66}, {11, 12, 65}, {13, 13, 67}, {14, 127, 65}, },
   * {{85, 85, 68}, {117, 117, 69}, },
   * {{76, 76, 70}, {108, 108, 71}, },
   * {{85, 117, -40}, },
   * {{76, 108, -41}, },
   * {{48, 117, -14}, },
   * {{97, 97, 72}, },
   * {{48, 122, -20}, },
   * {{48, 122, -20}, },
   * {{48, 122, -20}, },
   * {{48, 122, -20}, },
   * {{48, 122, -20}, },
   * {{48, 122, -20}, },
   * {},
   * {{48, 122, -20}, },
   * {{48, 110, -25}, {111, 111, 73}, {112, 122, 45}, },
   * {{48, 95, -20}, {97, 97, 74}, {98, 122, 45}, },
   * {{48, 95, -20}, {97, 116, 45}, {117, 117, 75}, {118, 122, 45}, },
   * {{48, 116, -56}, {117, 117, 76}, {118, 122, 45}, },
   * {{48, 115, -33}, {116, 116, 77}, {117, 122, 45}, },
   * {{48, 111, -31}, {112, 112, 78}, {113, 122, 45}, },
   * {{48, 110, -25}, {111, 111, 79}, {112, 115, 45}, {116, 116, 80}, {117, 122,
   * 45}, },
   * {{48, 95, -20}, {97, 97, 81}, {98, 122, 45}, },
   * {{48, 95, -20}, {97, 98, 45}, {99, 99, 82}, {100, 122, 45}, },
   * {{48, 95, -20}, {97, 113, 45}, {114, 114, 83}, {115, 122, 45}, },
   * {{48, 95, -20}, {97, 100, 45}, {101, 101, 84}, {102, 122, 45}, },
   * {{0, 41, 63}, {42, 42, 85}, {43, 127, 63}, },
   * {{0, 41, 86}, {42, 42, 87}, {43, 46, 86}, {47, 47, 88}, {48, 127, 86}, },
   * {{0, 127, -39}, },
   * {},
   * {{10, 10, 89}, },
   * {},
   * {},
   * {},
   * {},
   * {{114, 114, 90}, },
   * {{48, 107, -26}, {108, 108, 91}, {109, 122, 45}, },
   * {{48, 114, -24}, {115, 115, 92}, {116, 122, 45}, },
   * {{48, 95, -20}, {97, 97, 45}, {98, 98, 93}, {99, 122, 45}, },
   * {{48, 108, -29}, {109, 109, 94}, {110, 122, 45}, },
   * {{48, 100, -64}, {101, 101, 95}, {102, 122, 45}, },
   * {{48, 107, -26}, {108, 108, 96}, {109, 122, 45}, },
   * {{48, 116, -56}, {117, 117, 97}, {118, 122, 45}, },
   * {{48, 100, -64}, {101, 101, 98}, {102, 122, 45}, },
   * {{48, 95, -20}, {97, 112, 45}, {113, 113, 99}, {114, 122, 45}, },
   * {{48, 95, -20}, {97, 106, 45}, {107, 107, 100}, {108, 122, 45}, },
   * {{48, 95, -20}, {97, 104, 45}, {105, 105, 101}, {106, 122, 45}, },
   * {{48, 114, -24}, {115, 115, 102}, {116, 122, 45}, },
   * {{0, 41, 103}, {42, 42, 85}, {43, 46, 103}, {47, 47, 104}, {48, 127, 103},
   * },
   * {{0, 41, 105}, {42, 42, 106}, {43, 127, 105}, },
   * {{0, 127, -66}, },
   * {},
   * {},
   * {{103, 103, 107}, },
   * {{48, 122, -20}, },
   * {{48, 114, -24}, {115, 115, 108}, {116, 122, 45}, },
   * {{48, 107, -26}, {108, 108, 109}, {109, 122, 45}, },
   * {{48, 122, -20}, },
   * {{48, 109, -28}, {110, 110, 110}, {111, 122, 45}, },
   * {{48, 100, -64}, {101, 101, 111}, {102, 122, 45}, },
   * {{48, 115, -33}, {116, 116, 112}, {117, 122, 45}, },
   * {{48, 113, -63}, {114, 114, 113}, {115, 122, 45}, },
   * {{48, 116, -56}, {117, 117, 114}, {118, 122, 45}, },
   * {{48, 95, -20}, {97, 97, 115}, {98, 122, 45}, },
   * {{48, 109, -28}, {110, 110, 116}, {111, 122, 45}, },
   * {{48, 122, -20}, },
   * {{0, 41, 117}, {42, 42, 118}, {43, 127, 117}, },
   * {},
   * {{0, 127, -88}, },
   * {{0, 41, 86}, {42, 42, 106}, {43, 127, -66}, },
   * {{101, 101, 119}, },
   * {{48, 122, -20}, },
   * {{48, 100, -64}, {101, 101, 120}, {102, 122, 45}, },
   * {{48, 95, -20}, {97, 99, 45}, {100, 100, 121}, {101, 122, 45}, },
   * {{48, 108, -29}, {109, 109, 122}, {110, 122, 45}, },
   * {{48, 122, -20}, },
   * {{48, 95, -20}, {97, 101, 45}, {102, 102, 123}, {103, 122, 45}, },
   * {{48, 100, -64}, {101, 101, 124}, {102, 122, 45}, },
   * {{48, 95, -20}, {97, 102, 45}, {103, 103, 125}, {104, 122, 45}, },
   * {{48, 102, -117}, {103, 103, 126}, {104, 122, 45}, },
   * {{0, 127, -105}, },
   * {{0, 41, 103}, {42, 42, 118}, {43, 127, -87}, },
   * {{116, 116, 127}, },
   * {{48, 122, -20}, },
   * {{48, 114, -24}, {115, 115, 128}, {116, 122, 45}, },
   * {{48, 100, -64}, {101, 101, 129}, {102, 122, 45}, },
   * {{48, 95, -20}, {97, 97, 130}, {98, 122, 45}, },
   * {{48, 122, -20}, },
   * {{48, 100, -64}, {101, 101, 131}, {102, 122, 45}, },
   * {{48, 122, -20}, },
   * {},
   * {{48, 122, -20}, },
   * {{48, 109, -28}, {110, 110, 132}, {111, 122, 45}, },
   * {{48, 98, -62}, {99, 99, 133}, {100, 122, 45}, },
   * {{48, 122, -20}, },
   * {{48, 115, -33}, {116, 116, 134}, {117, 122, 45}, },
   * {{48, 100, -64}, {101, 101, 135}, {102, 122, 45}, },
   * {{48, 114, -24}, {115, 115, 136}, {116, 122, 45}, },
   * {{48, 122, -20}, },
   * {{45, 45, 137}, {48, 122, -20}, },
   * {{97, 97, 138}, },
   * {{108, 108, 139}, },
   * {{108, 108, 140}, },
   * {},
   * }
   * };
   */

  private static int[][] accept;

  static {
    try {
      DataInputStream s = new DataInputStream(new BufferedInputStream(
          Lexer.class.getResourceAsStream("lexer.dat")));

      // read gotoTable
      int length = s.readInt();
      gotoTable = new int[length][][][];
      for (int i = 0; i < gotoTable.length; i++) {
        length = s.readInt();
        gotoTable[i] = new int[length][][];
        for (int j = 0; j < gotoTable[i].length; j++) {
          length = s.readInt();
          gotoTable[i][j] = new int[length][3];
          for (int k = 0; k < gotoTable[i][j].length; k++) {
            for (int l = 0; l < 3; l++) {
              gotoTable[i][j][k][l] = s.readInt();
            }
          }
        }
      }

      // read accept
      length = s.readInt();
      accept = new int[length][];
      for (int i = 0; i < accept.length; i++) {
        length = s.readInt();
        accept[i] = new int[length];
        for (int j = 0; j < accept[i].length; j++) {
          accept[i][j] = s.readInt();
        }
      }

      s.close();
    } catch (Exception e) {
      throw new RuntimeException(
          "The file \"lexer.dat\" is either missing or corrupted.");
    }
  }

  public Lexer(@SuppressWarnings("hiding") PushbackReader in) {
    this.in = in;
  }

  @SuppressWarnings("unused")
  protected void filter() throws LexerException, IOException {
    // Do nothing
  }

  private int getChar() throws IOException {
    if (eof) {
      return -1;
    }

    int result = in.read();

    if (result == -1) {
      eof = true;
    }

    return result;
  }

  private String getText(int acceptLength) {
    StringBuffer s = new StringBuffer(acceptLength);
    for (int i = 0; i < acceptLength; i++) {
      s.append(text.charAt(i));
    }

    return s.toString();
  }

  protected Token getToken() throws IOException, LexerException {
    int dfa_state = 0;

    int start_pos = pos;
    int start_line = line;

    int accept_state = -1;
    int accept_token = -1;
    int accept_length = -1;
    int accept_pos = -1;
    int accept_line = -1;

    @SuppressWarnings("hiding")
    int[][][] gotoTable = Lexer.gotoTable[state.id()];
    @SuppressWarnings("hiding")
    int[] accept = Lexer.accept[state.id()];
    text.setLength(0);

    while (true) {
      int c = getChar();

      if (c != -1) {
        switch (c) {
        case 10:
          if (cr) {
            cr = false;
          } else {
            line++;
            pos = 0;
          }
          break;
        case 13:
          line++;
          pos = 0;
          cr = true;
          break;
        default:
          pos++;
          cr = false;
          break;
        }

        text.append((char)c);

        do {
          int oldState = dfa_state < -1 ? -2 - dfa_state : dfa_state;

          dfa_state = -1;

          int[][] tmp1 = gotoTable[oldState];
          int low = 0;
          int high = tmp1.length - 1;

          while (low <= high) {
            int middle = (low + high) / 2;
            int[] tmp2 = tmp1[middle];

            if (c < tmp2[0]) {
              high = middle - 1;
            } else if (c > tmp2[1]) {
              low = middle + 1;
            } else {
              dfa_state = tmp2[2];
              break;
            }
          }
        } while (dfa_state < -1);
      } else {
        dfa_state = -1;
      }

      if (dfa_state >= 0) {
        if (accept[dfa_state] != -1) {
          accept_state = dfa_state;
          accept_token = accept[dfa_state];
          accept_length = text.length();
          accept_pos = pos;
          accept_line = line;
        }
      } else {
        if (accept_state != -1) {
          switch (accept_token) {
          case 0: {
            @SuppressWarnings("hiding")
            Token token = new0(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 1: {
            @SuppressWarnings("hiding")
            Token token = new1(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 2: {
            @SuppressWarnings("hiding")
            Token token = new2(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 3: {
            @SuppressWarnings("hiding")
            Token token = new3(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 4: {
            @SuppressWarnings("hiding")
            Token token = new4(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 5: {
            @SuppressWarnings("hiding")
            Token token = new5(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 6: {
            @SuppressWarnings("hiding")
            Token token = new6(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 7: {
            @SuppressWarnings("hiding")
            Token token = new7(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 8: {
            @SuppressWarnings("hiding")
            Token token = new8(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 9: {
            @SuppressWarnings("hiding")
            Token token = new9(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 10: {
            @SuppressWarnings("hiding")
            Token token = new10(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 11: {
            @SuppressWarnings("hiding")
            Token token = new11(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 12: {
            @SuppressWarnings("hiding")
            Token token = new12(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 13: {
            @SuppressWarnings("hiding")
            Token token = new13(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 14: {
            @SuppressWarnings("hiding")
            Token token = new14(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 15: {
            @SuppressWarnings("hiding")
            Token token = new15(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 16: {
            @SuppressWarnings("hiding")
            Token token = new16(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 17: {
            @SuppressWarnings("hiding")
            Token token = new17(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 18: {
            @SuppressWarnings("hiding")
            Token token = new18(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 19: {
            @SuppressWarnings("hiding")
            Token token = new19(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 20: {
            @SuppressWarnings("hiding")
            Token token = new20(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 21: {
            @SuppressWarnings("hiding")
            Token token = new21(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 22: {
            @SuppressWarnings("hiding")
            Token token = new22(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 23: {
            @SuppressWarnings("hiding")
            Token token = new23(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 24: {
            @SuppressWarnings("hiding")
            Token token = new24(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 25: {
            @SuppressWarnings("hiding")
            Token token = new25(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 26: {
            @SuppressWarnings("hiding")
            Token token = new26(start_line + 1, start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 27: {
            @SuppressWarnings("hiding")
            Token token = new27(getText(accept_length), start_line + 1,
                start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 28: {
            @SuppressWarnings("hiding")
            Token token = new28(getText(accept_length), start_line + 1,
                start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 29: {
            @SuppressWarnings("hiding")
            Token token = new29(getText(accept_length), start_line + 1,
                start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 30: {
            @SuppressWarnings("hiding")
            Token token = new30(getText(accept_length), start_line + 1,
                start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 31: {
            @SuppressWarnings("hiding")
            Token token = new31(getText(accept_length), start_line + 1,
                start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 32: {
            @SuppressWarnings("hiding")
            Token token = new32(getText(accept_length), start_line + 1,
                start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 33: {
            @SuppressWarnings("hiding")
            Token token = new33(getText(accept_length), start_line + 1,
                start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          case 34: {
            @SuppressWarnings("hiding")
            Token token = new34(getText(accept_length), start_line + 1,
                start_pos + 1);
            pushBack(accept_length);
            pos = accept_pos;
            line = accept_line;
            return token;
          }
          }
        } else {
          if (text.length() > 0) {
            throw new LexerException("[" + (start_line + 1) + "," +
                (start_pos + 1) + "]" + " Unknown token: " + text);
          }

          @SuppressWarnings("hiding")
          EOF token = new EOF(start_line + 1, start_pos + 1);
          return token;
        }
      }
    }
  }

  Token new0(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TLAngleBracket(line, pos);
  }

  Token new1(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TRAngleBracket(line, pos);
  }

  Token new10(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TIntToken(line, pos);
  }

  Token new11(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TDoubleToken(line, pos);
  }

  Token new12(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TBoolToken(line, pos);
  }

  Token new13(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TOpaqueToken(line, pos);
  }

  Token new14(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TStringToken(line, pos);
  }

  Token new15(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TArrayToken(line, pos);
  }

  Token new16(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TInToken(line, pos);
  }

  Token new17(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TInoutToken(line, pos);
  }

  Token new18(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TPackageToken(line, pos);
  }

  Token new19(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TClassToken(line, pos);
  }

  Token new2(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TComma(line, pos);
  }

  Token new20(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TTargetToken(line, pos);
  }

  Token new21(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TInterfaceToken(line, pos);
  }

  Token new22(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TExtendsToken(line, pos);
  }

  Token new23(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TImplementsToken(line, pos);
  }

  Token new24(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TUsesToken(line, pos);
  }

  Token new25(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TAsToken(line, pos);
  }

  Token new26(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TEnumToken(line, pos);
  }

  Token
      new27(@SuppressWarnings("hiding") String text,
          @SuppressWarnings("hiding") int line,
          @SuppressWarnings("hiding") int pos) {
    return new TBlank(text, line, pos);
  }

  Token
      new28(@SuppressWarnings("hiding") String text,
          @SuppressWarnings("hiding") int line,
          @SuppressWarnings("hiding") int pos) {
    return new TDecimalConstant(text, line, pos);
  }

  Token
      new29(@SuppressWarnings("hiding") String text,
          @SuppressWarnings("hiding") int line,
          @SuppressWarnings("hiding") int pos) {
    return new TSignedDecimalNumber(text, line, pos);
  }

  Token new3(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TDot(line, pos);
  }

  Token
      new30(@SuppressWarnings("hiding") String text,
          @SuppressWarnings("hiding") int line,
          @SuppressWarnings("hiding") int pos) {
    return new TIdentifier(text, line, pos);
  }

  Token
      new31(@SuppressWarnings("hiding") String text,
          @SuppressWarnings("hiding") int line,
          @SuppressWarnings("hiding") int pos) {
    return new TTraditionalComment(text, line, pos);
  }

  Token
      new32(@SuppressWarnings("hiding") String text,
          @SuppressWarnings("hiding") int line,
          @SuppressWarnings("hiding") int pos) {
    return new TDocumentationComment(text, line, pos);
  }

  Token
      new33(@SuppressWarnings("hiding") String text,
          @SuppressWarnings("hiding") int line,
          @SuppressWarnings("hiding") int pos) {
    return new TEndOfLineComment(text, line, pos);
  }

  Token
      new34(@SuppressWarnings("hiding") String text,
          @SuppressWarnings("hiding") int line,
          @SuppressWarnings("hiding") int pos) {
    return new TConstant(text, line, pos);
  }

  Token new4(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TSemicolon(line, pos);
  }

  Token new5(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TLBrace(line, pos);
  }

  Token new6(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TRBrace(line, pos);
  }

  Token new7(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TLBracket(line, pos);
  }

  Token new8(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TRBracket(line, pos);
  }

  Token new9(@SuppressWarnings("hiding") int line,
      @SuppressWarnings("hiding") int pos) {
    return new TEquals(line, pos);
  }

  public Token next() throws LexerException, IOException {
    while (token == null) {
      token = getToken();
      filter();
    }

    Token result = token;
    token = null;
    return result;
  }

  public Token peek() throws LexerException, IOException {
    while (token == null) {
      token = getToken();
      filter();
    }

    return token;
  }

  /*
   * {
   * // INITIAL
   * {34, 27, 27, 27, 27, 7, 8, 2, -1, 3, -1, 29, 28, 4, 0, 9, 1, -1, 30, 30,
   * 30, -1, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 5, 6, 29, -1, -1, 34,
   * 34, 34, 34, 28, -1, 30, 30, 30, 30, 30, 30, 15, 25, 30, 30, 30, 30, 30, 30,
   * 16, 30, 30, 30, 30, -1, -1, -1, 33, 33, 34, 34, 34, 34, -1, 30, 30, 30, 30,
   * 30, 30, 30, 10, 30, 30, 30, 30, -1, -1, -1, 32, 33, -1, 12, 30, 30, 26, 30,
   * 30, 30, 30, 30, 30, 30, 24, -1, 31, -1, -1, -1, 19, 30, 30, 30, 17, 30, 30,
   * 30, 30, -1, -1, -1, 11, 30, 30, 30, 13, 30, 14, 20, 22, 30, 30, 18, 30, 30,
   * 30, 21, 30, -1, -1, -1, 23, },
   * 
   * };
   */

  private void pushBack(int acceptLength) throws IOException {
    int length = text.length();
    for (int i = length - 1; i >= acceptLength; i--) {
      eof = false;

      in.unread(text.charAt(i));
    }
  }

  protected void unread(@SuppressWarnings("hiding") Token token)
      throws IOException {
    @SuppressWarnings("hiding")
    String text = token.getText();
    int length = text.length();

    for (int i = length - 1; i >= 0; i--) {
      eof = false;

      in.unread(text.charAt(i));
    }

    pos = token.getPos() - 1;
    line = token.getLine() - 1;
  }
}
