using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace WindowsFormsApp1
{
    public partial class TubeEdit : Form
    {
        SolidBrush[] rgbBrush = new SolidBrush[32];
        Pen[] rgbPens = new Pen[32];
        Pen gridPen;
        int col_sel;
        int tile_sel;

        int[,,] tile = new int[32, 8, 8];
        int[,] map = new int[256, 16];
        int[,] map_dir = new int[256, 16];

        const int X_SIZE = (400 / 25);
        const int Y_SIZE = (600 / 25);

        int[] beeb_col = new int[24];
        int[,] cols = new int[24, 2];
        int[] def_tiles =
        {
                0x00000000,
                0x00000000,
                0x00000000,
                0x00000000,

                0x03030303,
                0x03030303,
                0x03030303,
                0x03030303,

                0x07070707,
                0x07070707,
                0x07070707,
                0x07070707,

                0x0000000f,
                0x00000f07,
                0x000f0707,
                0x0f070707,

                0x0f000000,
                0x070f0000,
                0x07070f00,
                0x0707070f,

                0x0f070707,
                0x000f0707,
                0x00000f07,
                0x0000000f,

                0x0707070f,
                0x07070f00,
                0x070f0000,
                0x0f000000,

                0x0f0f0f0f,
                0x0f03030f,
                0x0f03030f,
                0x0f0f0f0f,

                0x0f070707,
                0x0f070707,
                0x0f070707,
                0x0f070707,

                0x0707070f,
                0x0707070f,
                0x0707070f,
                0x0707070f
            };

        string[] def_map =
        {
            "AAAAAAAAAAAAAAAA",
         "ABBBBBBBBBBBBBBA",
         "ABBBCCCCCCCCBBBA",
         "ABBBCCCCCCCCBBBA",
         "ABBBCCCCCCCCBBBA",
         "ABBBCCCCCCCCBBBA",
         "ABBBBBBBBBBBBBBA",
         "AAAAAAAAAAAAAAAA",
         "AAAAAABBBBAAAAAA",
         "AAHAAABBBBAAAHAA",
         "AAAAAABBBBAAAAAA",
         "AAAAAABBBBAAAAAA",
         "AAAAAAICCJAAAAAA",
         "AAAAAAICCJAAAAAA",
         "AAAAAAICCJAAAAAA",
         "AAAAAAICCJAAAAAA",
         "AAAAADCCCCEAAAAA",
         "AAAADCCCCCCEAAAA",
         "AAADCCCGFCCCEAAA",
         "AADCCCGAAFCCCEAA",
         "ADCCCGAAAAFCCCEA",
         "DCCCGAAAAAAFCCCE",
         "CCCJAAAAAAAAICCC",
         "CCCJAAAAAAAAICCC",
         "CCCJAAAAAAAAICCC",
         "FCCCEAAAAAADCCCG",
         "AFCCCEAAAADCCCGA",
         "AAICCCEAADCCCJAA",
         "AAICCCJAAICCCJAA",
         "AAICCCJAAICCCJAA",
         "AAICCCJAAICCCJAA",
         "AAICCCJAAICCCJAA"
        };

        Bitmap[] i = new Bitmap[11];
        /*        const int[] def_tiles =
                {
                    0,0,0,0,
                    0,0,0,0
                };*/

        int ui_mode = 0;
        int dir_sel = 0;

        private int make_beeb_col(SolidBrush brush)
        {
            int val = 0;
            int r, g, b;

            r = brush.Color.R;
            g = brush.Color.G;
            b = brush.Color.B;

            if (r != 0)
                val |= 0x01;
            if (r > 128)
                val |= 0x02;
            if (g != 0)
                val |= 0x04;
            if (g > 128)
                val |= 0x08;
            if (b != 0)
                val |= 0x10;
            if (b > 128)
                val |= 0x20;

            return val;
        }
        public TubeEdit()
        {
            int x, y;

            InitializeComponent();

            rgbBrush[0] = new SolidBrush(Color.FromArgb(0, 0, 0));
            rgbBrush[1] = new SolidBrush(Color.FromArgb(255, 0, 0));
            rgbBrush[2] = new SolidBrush(Color.FromArgb(0, 255, 0));
            rgbBrush[3] = new SolidBrush(Color.FromArgb(255, 255, 0));
            rgbBrush[4] = new SolidBrush(Color.FromArgb(0, 0, 255));
            rgbBrush[5] = new SolidBrush(Color.FromArgb(255, 0, 255));
            rgbBrush[6] = new SolidBrush(Color.FromArgb(0, 255, 255));
            rgbBrush[7] = new SolidBrush(Color.FromArgb(255, 255, 255));
            rgbBrush[8] = new SolidBrush(Color.FromArgb(0, 0, 0));
            rgbBrush[9] = new SolidBrush(Color.FromArgb(128, 0, 0));
            rgbBrush[10] = new SolidBrush(Color.FromArgb(0, 128, 0));
            rgbBrush[11] = new SolidBrush(Color.FromArgb(128, 128, 0));
            rgbBrush[12] = new SolidBrush(Color.FromArgb(0, 0, 128));
            rgbBrush[13] = new SolidBrush(Color.FromArgb(128, 0, 128));
            rgbBrush[14] = new SolidBrush(Color.FromArgb(0, 128, 128));
            rgbBrush[15] = new SolidBrush(Color.FromArgb(128, 128, 128));

            rgbBrush[16] = new SolidBrush(Color.FromArgb(255, 128,   0));
            rgbBrush[17] = new SolidBrush(Color.FromArgb(255,   0, 128));
            rgbBrush[18] = new SolidBrush(Color.FromArgb(255, 128, 128));
            rgbBrush[19] = new SolidBrush(Color.FromArgb(128, 255,   0));
            rgbBrush[20] = new SolidBrush(Color.FromArgb(  0, 255, 128));
            rgbBrush[21] = new SolidBrush(Color.FromArgb(128, 255, 128));
            rgbBrush[22] = new SolidBrush(Color.FromArgb(128,   0, 255));
            rgbBrush[23] = new SolidBrush(Color.FromArgb(  0, 128, 255));
            rgbBrush[8] =  new SolidBrush(Color.FromArgb(128, 128, 255));

            for (int c = 0; c < 24; c++)
                rgbPens[c] = new Pen(rgbBrush[c].Color);
            for (int c = 0; c < 24; c++)
            {
                beeb_col[c] = make_beeb_col(rgbBrush[c]);
                cols[c,0] = cols[c,1] = 0;
                if ((beeb_col[c] & 0x01) != 0)
                    cols[c, 0] |= 1;
                if ((beeb_col[c] & 0x04) != 0)
                    cols[c, 0] |= 2;
                if ((beeb_col[c] & 0x10) != 0)
                    cols[c, 0] |= 4;
                if ((beeb_col[c] & 0x02) != 0)
                    cols[c, 1] |= 1;
                if ((beeb_col[c] & 0x08) != 0)
                    cols[c, 1] |= 2;
                if ((beeb_col[c] & 0x20) != 0)
                    cols[c, 1] |= 4;
            }

            gridPen = new Pen(Color.Gray);

            col_sel = 0;
            tile_sel = 0;

            vScrollBar1.Value = 231;

            for (int c = 0; c < 10; c++)
            {
                for (y = 0; y < 4; y++)
                {
                    for (x = 0; x < 8; x += 2)
                    {
                        int dat = def_tiles[c * 4 + y];
                        int col = 0;

                        dat = (dat >> ((x & 6) * 4)) & 0xff;

                        for (int d = 0; d < 24; d++)
                        {
                            if (dat == beeb_col[d])
                                col = d;
                        }

                        tile[c, (3 - y) * 2, 7 - x] = cols[col,0];
                        tile[c, (3 - y) * 2 + 1, 7 - x] = cols[col,0];
                        tile[c, (3 - y) * 2, 7 - (x+1)] = cols[col, 1];
                        tile[c, (3 - y) * 2 + 1, 7 - (x+1)] = cols[col, 1];
                    }
                }
            }

            for (y = 0; y < 32; y++)
            {
                for (x = 0; x < 16; x++)
                {
                    char m = def_map[y][x];
                    map[y, x] = m - 'A';
                }
            }
            
            i[0] = new Bitmap("a0.bmp");
            i[1] = new Bitmap("a1.bmp");
            i[2] = new Bitmap("a2.bmp");
            i[3] = new Bitmap("a3.bmp");
            i[4] = new Bitmap("a4.bmp");
            i[5] = new Bitmap("a5.bmp");
            i[6] = new Bitmap("a6.bmp");
            i[7] = new Bitmap("a7.bmp");
            i[8] = new Bitmap("a8.bmp");
            i[9] = new Bitmap("a9.bmp");
            i[10] = new Bitmap("a10.bmp");
            for (int c = 0; c < 11; c++)
                i[c].MakeTransparent(Color.FromArgb(0,0,0));
        }

        private void panel2_Paint(object sender, PaintEventArgs e)
        {
            Panel panel = sender as Panel;
            Graphics dc = e.Graphics;

            SolidBrush backgroundBrush = new SolidBrush(Color.Black);
            int x, y;

            dc.FillRectangle(backgroundBrush,
                                         0,
                                         0,
                                         192,
                                         192);

            for (y = 0; y < 8; y++)
            {
                for (x = 0; x < 8; x++)
                {
                    dc.FillRectangle(rgbBrush[tile[tile_sel, y, x]], x * 24, y * 24, 24, 24);
                }
            }

            for (y = 1; y < 8; y++)
            {
                dc.DrawLine(gridPen, 0, y * 24, 192, y * 24);
            }
            for (x = 1; x < 4; x++)
            {
                dc.DrawLine(gridPen, x * 48, 0, x * 48, 192);
            }
        }

        private void panel3_Paint(object sender, PaintEventArgs e)
        {
            Panel panel = sender as Panel;
            Graphics dc = e.Graphics;
            int x, y;

            for (int c = 0; c < 24; c++)
            {
                x = (c & 7) * 24;
                y = ((c & 24) >> 3) * 24;

                //       dc.FillRectangle(rgbBrush[c], x, y, 24, 24);
                for (int xx = 0; xx < 24; xx++)
                    dc.DrawLine(rgbPens[cols[c,xx&1]], x + xx, y, x + xx, y + 23);
            }

            x = (col_sel & 7) * 24;
            y = ((col_sel & 24) >> 3) * 24;

            dc.DrawLine(gridPen, x, y, x + 23, y);
            dc.DrawLine(gridPen, x, y, x, y + 23);
            dc.DrawLine(gridPen, x, y + 23, x + 23, y + 23);
            dc.DrawLine(gridPen, x + 23, y, x + 23, y + 23);
            dc.DrawLine(gridPen, x, y + 1, x + 22, y + 1);
            dc.DrawLine(gridPen, x + 1, y, x + 1, y + 23);
            dc.DrawLine(gridPen, x, y + 22, x + 22, y + 22);
            dc.DrawLine(gridPen, x + 22, y, x + 22, y + 23);
        }

        private void panel3_Click(object sender, EventArgs e)
        {

        }

        private void panel3_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                Point p = e.Location;

                col_sel = ((p.X / 24) & 7) + (((p.Y / 24) & 3) * 8);

                panel3.Invalidate();
                panel3.Update();
            }
        }

        bool panel2_wasdown = false;
        private void panel2_MouseDown(object sender, MouseEventArgs e)
        {
            Point p = e.Location;

            int x = (p.X / 24) & ~1;
            int y = p.Y / 24;

            Rectangle r = new Rectangle();

            r.X = p.X - (p.X % 48);
            r.Y = p.Y - (p.Y % 24);
            r.Width = 48;
            r.Height = 24;

            if (y < 0 || y >= 8)
                return;
            if (x < 0 || x >= 8)
                return;

            if (e.Button == MouseButtons.Left)
            {
                tile[tile_sel, y, x] = cols[col_sel, 0];
                tile[tile_sel, y, x+1] = cols[col_sel, 1];

                //panel1.Invalidate();
                //panel1.Update();
                panel2.Invalidate(r);
                panel2.Update();
                //panel4.Invalidate();
                //panel4.Update();
                panel2_wasdown = true;
            }
            if (e.Button == MouseButtons.Right)
            {
                tile[tile_sel, y, x] = 0;
                tile[tile_sel, y, x+1] = 0;

                //panel1.Invalidate();
                //panel1.Update();
                panel2.Invalidate(r);
                panel2.Update();
                //panel4.Invalidate();
                //panel4.Update();
                panel2_wasdown = true;
            }
        }

        private void panel2_MouseMove(object sender, MouseEventArgs e)
        {
            panel2_MouseDown(sender, e);
        }

        private void panel2_MouseUp(object sender, MouseEventArgs e)
        {
            if (panel2_wasdown)
            {
                panel2_wasdown = false;
                panel1.Invalidate();
                panel1.Update();
                panel4.Invalidate();
                panel4.Update();
            }
        }

        private void panel4_Paint(object sender, PaintEventArgs e)
        {
            Panel panel = sender as Panel;
            Graphics dc = e.Graphics;

            SolidBrush backgroundBrush = new SolidBrush(Color.Black);
            int c;

            dc.FillRectangle(backgroundBrush,
                                         0,
                                         0,
                                         192,
                                         192);

            if (ui_mode == 1)
            {
                for (c = 0; c < 11; c++)
                {
                    int off_x = (c & 3) * 48;
                    int off_y = ((c >> 2) & 7) * 48;

                    dc.DrawImage(i[c], new Point(off_x, off_y));
                    

                    if (c == dir_sel)
                    {
                        dc.DrawLine(gridPen, off_x, off_y, off_x + 47, off_y);
                        dc.DrawLine(gridPen, off_x, off_y, off_x, off_y + 47);
                        dc.DrawLine(gridPen, off_x, off_y + 47, off_x + 47, off_y + 47);
                        dc.DrawLine(gridPen, off_x + 47, off_y, off_x + 47, off_y + 47);
                        dc.DrawLine(gridPen, off_x, off_y + 1, off_x + 46, off_y + 1);
                        dc.DrawLine(gridPen, off_x + 1, off_y, off_x + 1, off_y + 46);
                        dc.DrawLine(gridPen, off_x, off_y + 46, off_x + 46, off_y + 46);
                        dc.DrawLine(gridPen, off_x + 46, off_y, off_x + 46, off_y + 46);
                    }
                }
            }
            else
            {
                for (c = 0; c < 32; c++)
                {
                    int x, y;
                    int off_x = (c & 3) * 48;
                    int off_y = ((c >> 2) & 7) * 48;

                    for (y = 0; y < 8; y++)
                    {
                        for (x = 0; x < 8; x++)
                        {
                            dc.FillRectangle(rgbBrush[tile[c, y, x]], (x * 6) + off_x, (y * 6) + off_y, 6, 6);

                            if (c == tile_sel)
                            {
                                dc.DrawLine(gridPen, off_x, off_y, off_x + 47, off_y);
                                dc.DrawLine(gridPen, off_x, off_y, off_x, off_y + 47);
                                dc.DrawLine(gridPen, off_x, off_y + 47, off_x + 47, off_y + 47);
                                dc.DrawLine(gridPen, off_x + 47, off_y, off_x + 47, off_y + 47);
                                dc.DrawLine(gridPen, off_x, off_y + 1, off_x + 46, off_y + 1);
                                dc.DrawLine(gridPen, off_x + 1, off_y, off_x + 1, off_y + 46);
                                dc.DrawLine(gridPen, off_x, off_y + 46, off_x + 46, off_y + 46);
                                dc.DrawLine(gridPen, off_x + 46, off_y, off_x + 46, off_y + 46);
                            }
                        }
                    }
                }
            }
        }

        private void panel4_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                Point p = e.Location;

                int x = p.X / 48;
                int y = p.Y / 48;

                if (ui_mode == 1)
                {
                    int old_dir_sel = dir_sel;

                    dir_sel = x + (y * 4);
                    if (dir_sel > 10)
                        dir_sel = 10;

                    if (dir_sel != old_dir_sel)
                    {
                        panel4.Invalidate();
                        panel4.Update();
                    }
                }
                else
                {
                    int old_tile_sel = tile_sel;

                    tile_sel = x + (y * 4);

                    if (tile_sel != old_tile_sel)
                    {
                        panel2.Invalidate();
                        panel2.Update();
                        panel4.Invalidate();
                        panel4.Update();
                    }
                }
            }
        }

        private void panel4_MouseMove(object sender, MouseEventArgs e)
        {
            panel4_MouseDown(sender, e);
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            Panel panel = sender as Panel;
            Graphics dc = e.Graphics;

            int x, y;

            int vscroll = 232 - vScrollBar1.Value;

            System.Diagnostics.Debug.WriteLine(String.Format("{0} {1}", vscroll, vScrollBar1.Value));

            for (y = 0; y < Y_SIZE; y++)
            {
                for (x = 0; x < X_SIZE; x++)
                {
                    int off_x = x * 25;
                    int off_y = (Y_SIZE - y - 1) * 25;

                    int xx, yy;

                    int c = map[y + vscroll, x];

                    for (yy = 0; yy < 8; yy++)
                    {
                        for (xx = 0; xx < 8; xx++)
                        {
                            dc.FillRectangle(rgbBrush[tile[c, yy, xx]],
                                    (xx * 3) + off_x,
                                    (yy * 3) + off_y,
                                    3,
                                    3);
                        }
                    }
                    if (ui_mode == 1)
                        dc.DrawImage(i[map_dir[y + vscroll, x]], off_x, off_y, 24, 24);
                }
            }

            for (y = 1; y < Y_SIZE; y++)
                dc.DrawLine(gridPen, 0, y * 25, 400, y * 25);
            for (x = 1; x < X_SIZE; x++)
                dc.DrawLine(gridPen, x * 25, 0, x * 25, 600);
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            Point p = e.Location;
            int vscroll = 231 - vScrollBar1.Value;

            int x = p.X / 25;
            int y = Y_SIZE - (p.Y / 25);// - 1;
            int y2 = y;
            Rectangle r = new Rectangle();

            r.X = p.X - (p.X % 25);
            r.Y = p.Y - (p.Y % 25);
            r.Width = 25;
            r.Height = 25;

            y += vscroll;
            System.Diagnostics.Debug.WriteLine(String.Format("{0} {1}", y2, y));

            if (y < 0)
                return;
            if (x < 0 || x > 15)
                return;

            if (e.Button == MouseButtons.Left)
            {
                if (ui_mode == 1)
                {
                    if (map_dir[y, x] != dir_sel)
                    {
                        map_dir[y, x] = dir_sel;
                        panel1.Invalidate(r);
                        panel1.Update();
                        //panel1.Refresh();
                    }
                }
                else
                {
                    if (map[y, x] != tile_sel)
                    {
                        map[y, x] = tile_sel;
                        panel1.Invalidate(r);
                        panel1.Update();
                        //panel1.Refresh();
                    }
                }
            }
            if (e.Button == MouseButtons.Right)
            {
                if (ui_mode == 1)
                {
                    if (map_dir[y, x] != 9)
                    {
                        map_dir[y, x] = 9;
                        panel1.Invalidate(r);
                        panel1.Update();
                        //panel1.Refresh();
                    }
                }
                else
                {
                    if (map[y, x] != 0)
                    {
                        map[y, x] = 0;
                        panel1.Invalidate(r);
                        panel1.Update();
                        //panel1.Refresh();
                    }
                }
            }
        }

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            panel1_MouseDown(sender, e);
        }

        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            panel1.Invalidate();
            panel1.Refresh();
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Stream myStream;
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();

            saveFileDialog1.Filter = "level (*.)|*.|All files (*.*)|*.*";
            saveFileDialog1.FilterIndex = 2;
            saveFileDialog1.RestoreDirectory = true;

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if ((myStream = saveFileDialog1.OpenFile()) != null)
                {
                    for (int c = 0; c < 32; c++)
                    {
                        for (int y = 7; y >= 0; y--)
                        {
                            for (int x = 0; x < 8; x += 2)
                            {
                                Byte data = 0;

                                if ((tile[c, y, x] & 1) != 0)
                                    data |= 0x01;
                                if ((tile[c, y, x] & 2) != 0)
                                    data |= 0x04;
                                if ((tile[c, y, x] & 4) != 0)
                                    data |= 0x10;
                                if ((tile[c, y, x] & 8) != 0)
                                    data |= 0x40;

                                if ((tile[c, y, x + 1] & 1) != 0)
                                    data |= 0x02;
                                if ((tile[c, y, x + 1] & 2) != 0)
                                    data |= 0x08;
                                if ((tile[c, y, x + 1] & 4) != 0)
                                    data |= 0x20;
                                if ((tile[c, y, x + 1] & 8) != 0)
                                    data |= 0x80;

                                myStream.WriteByte(data);
                            }
                        }
                    }
                    for (int y = 0; y < 256; y++)
                    {
                        for (int x = 0; x < 16; x++)
                        {
                            Byte data = (Byte)map[y, x];
                            myStream.WriteByte(data);
                        }
                    }
                    for (int y = 0; y < 256; y++)
                    {
                        for (int x = 0; x < 16; x++)
                        {
                            Byte data = (Byte)map_dir[y, x];
                            myStream.WriteByte(data);
                        }
                    }
                    // Code to write the stream goes here.
                    myStream.Close();
                }
            }
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Stream myStream;
            OpenFileDialog openFileDialog1 = new OpenFileDialog();

            openFileDialog1.Filter = "level (*.)|*.|All files (*.*)|*.*";
            openFileDialog1.FilterIndex = 2;
            openFileDialog1.RestoreDirectory = true;

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if ((myStream = openFileDialog1.OpenFile()) != null)
                {
                    for (int c = 0; c < 32; c++)
                    {
                        for (int y = 7; y >= 0; y--)
                        {
                            for (int x = 0; x < 8; x += 2)
                            {
                                Byte dat = (Byte)myStream.ReadByte();
                                int col = 0;

                                for (int d = 0; d < 24; d++)
                                {
                                    if (dat == beeb_col[d])
                                        col = d;
                                }

                                tile[c, y, x] = cols[col, 0];
                                tile[c, y, x + 1] = cols[col, 1];
                            }
                        }
                    }

                    for (int y = 0; y < 256; y++)
                    {
                        for (int x = 0; x < 16; x++)
                        {
                            map[y, x] = myStream.ReadByte();
                        }
                    }
                    for (int y = 0; y < 256; y++)
                    {
                        for (int x = 0; x < 16; x++)
                        {
                            map_dir[y, x] = myStream.ReadByte();
                        }
                    }

                    myStream.Close();
                }
            }
            panel1.Invalidate();
            panel1.Update();
            panel2.Invalidate();
            panel2.Update();
            panel4.Invalidate();
            panel4.Update();
        }

        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void TubeEdit_Load(object sender, EventArgs e)
        {

        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton1.Checked)
            {
                radioButton2.Checked = false;
                ui_mode = 0;
                panel1.Invalidate();
                panel1.Update();
                panel4.Invalidate();
                panel4.Update();
            }
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton2.Checked)
            {
                radioButton1.Checked = false;
                ui_mode = 1;
                panel1.Invalidate();
                panel1.Update();
                panel4.Invalidate();
                panel4.Update();
            }
        }
    }
}
