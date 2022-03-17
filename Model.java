import java.awt.image.BufferedImage;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.text.Normalizer;
import java.util.Iterator;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.IIOException;
import javax.imageio.ImageIO;
import javax.imageio.ImageWriter;
import javax.imageio.stream.FileImageOutputStream;
import javax.imageio.stream.ImageOutputStream;
import java.awt.Color;

/**
 *
 * @author Sango
 */
public class Model {

    public static void main(String[] args){
        
        System.out.println("Hola Mundo");
        //System.out.println("Hola Mundo2");
        Model m = new Model();
        
        BufferedImage imagen = m.readImage("star wars.jpg");
        BufferedImage imagen2 = m.readImage("Revan.jpg");
        BufferedImage imagen3;
        

        int w = imagen.getWidth();
        int h = imagen.getHeight();
        int w2 = imagen2.getWidth();
        int h2 = imagen2.getHeight();
        //Color 
        
        BufferedImage newImage = new BufferedImage(imagen.getWidth(),
                imagen.getHeight(),
                BufferedImage.TYPE_3BYTE_BGR);
                
        
        //red filter
        /*for (int i =0; i < w-1; i++)
        {
            for (int j =0; j < h-1; j++)
            {
                Color color = new Color(imagen.getRGB(i, j));
                imagen.setRGB(i,j, new Color(color.getRed(),0,0).getRGB());
                //System.out.println("Hola Mundo2"); 
            }
        }*/
        //blue filter
        /*for (int i =0; i < w-1; i++)
        {
            for (int j =0; j < h-1; j++)
            {
                Color color = new Color(imagen.getRGB(i, j));
                imagen.setRGB(i,j, new Color(0,0,color.getBlue()).getRGB());
                //System.out.println("Hola Mundo2"); 
            }
        }*/
        //green filter
        /*for (int i =0; i < w-1; i++)
        {
            for (int j =0; j < h-1; j++)
            {
                Color color = new Color(imagen.getRGB(i, j));
                imagen.setRGB(i,j, new Color(0,color.getGreen(),0).getRGB());
                //System.out.println("Hola Mundo2"); 
            }
        }*/
        //black and white filter
        /*for (int i =0; i < w-1; i++)
        {
            for (int j =0; j < h-1; j++)
            {
                Color color = new Color(imagen.getRGB(i, j));
                int bandw = color.getBlue() + color.getRed() + color.getGreen();
                imagen.setRGB(i,j, new Color(bandw/3, bandw/3, bandw/3).getRGB());
                //System.out.println(bandw); 
            }
        }*/
        //high contrast
        /*for (int i =0; i < w-1; i++)
        {
            for (int j =0; j < h-1; j++)
            {
                Color color = new Color(imagen.getRGB(i, j));
                int bandw = color.getBlue() + color.getRed()*65536 + color.getGreen()*256;
                //if (bandw <= 256)
                if (bandw >= 8388608)
                {
                    bandw = 255;
                    imagen.setRGB(i,j, new Color(bandw, bandw, bandw).getRGB());
                }
                else 
                {
                    imagen.setRGB(i,j, new Color(0, 0, 0).getRGB());
                }
                
                //System.out.println(bandw); 
            }
        }*/
        //inverso
        /*for (int i =0; i < w-1; i++)
        {
            for (int j =0; j < h-1; j++)
            {
                Color color = new Color(imagen.getRGB(i, j));
                int bandw = color.getBlue() + color.getRed()*65536 + color.getGreen()*256;
                //if (bandw <= 256)
                if (bandw <= 8388608)
                {
                    bandw = 255;
                    imagen.setRGB(i,j, new Color(bandw, bandw, bandw).getRGB());
                }
                else 
                {
                    imagen.setRGB(i,j, new Color(0, 0, 0).getRGB());
                }
                
                //System.out.println(bandw); 
            }
        }*/
        //sepia
        /*for (int i =0; i < w-1; i++)
        {
            for (int j =0; j < h-1; j++)
            {
                Color color = new Color(imagen.getRGB(i, j));
                int red = (int) (color.getRed()*0.393f + color.getGreen()*0.769f + color.getBlue()*0.189f);
                int green = (int)(color.getRed()*0.349f + color.getGreen()*0.686f + color.getBlue()*0.168f);
                int blue = (int)(color.getRed()*0.272f + color.getGreen()*0.534f + color.getBlue()*0.131f);
                if (red > 255)
                {
                    red = 255;
                }
                if (green > 255)
                {
                    green = 255;
                }
                if (blue > 255)
                {
                    blue = 255;
                }
                //System.out.println("r" + red + " g " + green + " b " + blue);
                imagen.setRGB(i,j, new Color(red, green, blue).getRGB());
                
                //System.out.println(bandw); 
            }
        }*/
        //blur
        /*double [][] matrix = {{0,.2,0}, {.2,.2,.2}, {0,.2,0}};
       
        for (int i =0; i < w-1; i++)
        {
            for (int j =0; j < h-1; j++)
            {
                for (int x =0; x < matrix.length; x++)
                {
                    for (int y =0; y < matrix.length; y++)
                    {
                        if (i+1 > w || j+1>h)
                        {
                            
                            break;
                        }
                        if (i-1 < 0 || j-1<0)
                        {
                            
                            
                            break;
                        }
                        //System.out.println(matrix[x][y]);
                        
                        Color color = new Color(imagen.getRGB((i+(x-1)), (j+(y-1))));

                    }
                    
                 }
                 
            }
            
        }*/
       // blending
        for (int i =0; i < w-1; i++)
        {
            for (int j =0; j < h-1; j++)
            {
                Color color = new Color(imagen.getRGB(i, j));
                int red1 = (int) (color.getRed() + color.getGreen() + color.getBlue());
                int green1 = (int)(color.getRed() + color.getGreen() + color.getBlue());
                int blue1 = (int)(color.getRed() + color.getGreen() + color.getBlue());
                //Color color = new Color(imagen.getRGB(i, j));
                imagen.setRGB(i,j, new Color(0,0,0).getRGB()); 
                for (int a =0; a < w2-1; a++)
                {
                    for (int b =0; b < h2-1; b++)
                    {
                        Color color2 = new Color(imagen2.getRGB(a, b));
                        int red2 = (int) (color2.getRed() + color2.getGreen() + color2.getBlue());
                        int green2 = (int)(color2.getRed() + color2.getGreen() + color2.getBlue());
                        int blue2 = (int)(color2.getRed() + color2.getGreen() + color2.getBlue());
                //Color color = new Color(imagen.getRGB(i, j));
                        imagen2.setRGB(a,b, new Color(0,0,0).getRGB());
                        int redf = red1 + red2;
                        int greenf = green1 + green2;
                        int bluef = blue1 + blue2;
                        //imagen3 = imagen + imagen2;

                    }
                //imagen.setRGB(i,j, new Color(color.getRed(),0,0).getRGB());
                //System.out.println("Hola Mundo2"); 
                }
                
            }
        }
        
            
        //imagen3 = (imagen) + (imagen2);
        



        
        m.writeImage(newImage,"try", "jpg");
        
        
        
        
       
        
       
        //m.writeImage(imagen, "starwars_blur", "jpg");
       
        //System.out.println("mult"+ red);
        
    }

    
    public BufferedImage readImage(String pathname) {
        
        try {

            return ImageIO.read(new File(pathname));

        } catch (IOException ioe) {
            System.out.println("Can't open image.");
            System.exit(1);
        }

        return null;
    }

    public BufferedImage readImage(File file) {

        try {

            return ImageIO.read(file);

        } catch (IOException ioe) {
            System.out.println("Can't open image.");
            System.exit(1);
        }

        return null;
    }

    public void writeImage(BufferedImage imagen, String pathName, String extension) {

        try {
            
            ImageIO.write(imagen, extension, new File(pathName + "."
                    + extension));

        } catch (IOException ioe) {
            System.out.println("Can't save image.");
            ioe.printStackTrace();
        }
    }


    private void println(String s) {
        System.out.println(s);
    }
}
