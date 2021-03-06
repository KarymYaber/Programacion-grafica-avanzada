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
        BufferedImage newImage = new BufferedImage(imagen.getWidth(),imagen.getHeight(),BufferedImage.TYPE_3BYTE_BGR);
        BufferedImage bigImage = new BufferedImage(imagen.getWidth()*2, imagen.getHeight()*2, BufferedImage.TYPE_3BYTE_BGR);
        BufferedImage smallImage = new BufferedImage(imagen2.getWidth(), imagen2.getHeight(), BufferedImage.TYPE_3BYTE_BGR);

            int w = imagen.getWidth();
            int h = imagen.getHeight();
            int w2 = imagen2.getWidth();
            int h2 = imagen2.getHeight();
            int widthS = bigImage.getWidth();  
            int heightS = bigImage.getHeight();  
            
        //scale filter big
        /*float redscale=0f; 
        float greenscale=0f; 
        float bluescale=0f;
        for (int i =0; i < w-1; i++)
        {
            

            for (int j =0; j < h-1; j++)
            {
                        
                        
                
                Color color = new Color(imagen2.getRGB(i, j));
                    
                        //smallImage.setRGB((i*2),  (j*2),   color.getRGB());
                        //smallImage.setRGB((i*2),  (j*2)+1, color.getRGB());
                        //smallImage.setRGB((i*2)+1,(j*2),   color.getRGB());
                        //smallImage.setRGB((i*2)+1,(j*2)+1, color.getRGB()); 
                        redscale = (color.getRed());
                        greenscale = (color.getGreen());
                        bluescale = (color.getBlue());

                        if (redscale > 255)
                        {
                            redscale = 255;
                        }
                    if (greenscale > 255)
                        {
                            greenscale = 255;
                        }
                    if (bluescale > 255)
                        {
                            bluescale = 255;
                        }
                    if (redscale < 0)
                        {
                            redscale = 255;
                        }
                    if (greenscale < 0)
                        {
                            greenscale = 255;
                        }
                    if (bluescale < 0)
                        {
                            bluescale = 255;
                        }
                        
                        
                        smallImage.setRGB(i*2,j*2, new Color((int)redscale, (int)greenscale, (int)bluescale ).getRGB());

                        
                        
            }
                           
        }*/
        
        //small filter
        float redscale=0f; 
        float greenscale=0f; 
        float bluescale=0f;
        for (int i =0; i < w-1; i++)
        {
            

            for (int j =0; j < h-1; j++)
            {
                        
                        
                
                Color color = new Color(imagen.getRGB(i, j));
                        
                        
                        redscale = (color.getRed());
                        greenscale = (color.getGreen());
                        bluescale = (color.getBlue());

                        
                        if (redscale > 255)
                        {
                            redscale = 255;
                        }
                    if (greenscale > 255)
                        {
                            greenscale = 255;
                        }
                    if (bluescale > 255)
                        {
                            bluescale = 255;
                        }
                    if (redscale < 0)
                        {
                            redscale = 255;
                        }
                    if (greenscale < 0)
                        {
                            greenscale = 255;
                        }
                    if (bluescale < 0)
                        {
                            bluescale = 255;
                        }
                bigImage.setRGB(i,j, new Color((int)redscale, (int)greenscale, (int)bluescale ).getRGB());
                        
                        
            }
                           
        }
        
            /*
        
            
            //hybrid filter
            int percentage = 50;                        
            float imag1 = percentage / 100f;
            float imag2 = 1f - imag1;
            double [][] matrixblur = {{0,.2,0}, {.2,.2,.2}, {0,.2,0}};
            double [][] matrixbordes = {{0,1,0}, {1,-4,1}, {0,1,0}};
            for (int i =0; i < w2-1 && i < w-1; i++)
            {
    
                for (int j =0; j < h2-1 && j < h-1; j++)
                { 
                    
                    double redb = 0;
                    double greenb = 0;
                    double blueb = 0;
                    double redbor = 0;
                    double greenbor = 0;
                    double bluebor = 0;
                    int redacum = 0;
                    int greenacum = 0;
                    int blueacum = 0;
                 for (int x =0; x < matrixblur.length && x < matrixbordes.length; x++)
                 {
                     for (int y =0; y < matrixblur.length && y < matrixbordes.length; y++)
                     {
                        if ((i+(x-1) < w && j+(y-1) < h ) && (i+(x-1) > 0 && j+(y-1) > 0 ))
                        {
                            //blur
                            
                            Color color = new Color(imagen.getRGB(i+(x-1), j+(y-1)));
                           
                            double red = (double)(color.getRed());
                            redb = redb + matrixblur[x][y] * red;
                            double green = (double)(color.getGreen());
                            greenb = greenb + matrixblur[x][y] * green;
                            double blue = (double)(color.getBlue());
                            blueb = blueb + matrixblur[x][y] * blue;
                            //bordes
                            Color color2 = new Color(imagen2.getRGB(i+(x-1), j+(y-1)));
                            double redbordes = (double)(color2.getRed());
                            redbor = redbor + matrixbordes[x][y] * redbordes;
                            double greenbordes = (double)(color2.getGreen());
                            greenbor = greenbor + matrixbordes[x][y] * greenbordes;
                            double bluebordes = (double)(color2.getBlue());
                            bluebor = bluebor + matrixbordes[x][y] * bluebordes;
                            
                            
                            
                            redacum = Math.round(((int)redb * imag1) + ((int)redbor   * imag2));
                            greenacum = Math.round(((int)greenb * imag1) + ((int)greenbor * imag2));
                            blueacum = Math.round(((int)blueb  * imag1) + ((int)redbor  * imag2));

                        }
                            if (redacum > 255)
                                {
                                    redacum = 255;
                                }
                            if (greenacum > 255)
                                {
                                    greenacum = 255;
                                }
                            if (blueacum > 255)
                                {
                                    blueacum = 255;
                                }
                            if (redacum < 0)
                                {
                                    redacum = 255;
                                }
                            if (greenacum < 0)
                                {
                                    greenacum = 255;
                                }
                            if (blueacum < 0)
                                {
                                    blueacum = 255;
                                }
                                
                            
                        }

                     }
                     newImage.setRGB(i,j,new Color(redacum, greenacum, blueacum).getRGB());  
                  }
                }
                
            
                    

            //blending filter
            /*int percentage = 50;                        
            float imag1 = percentage / 100f;
            float imag2 = 1f - imag1;
            
            for (int i =0; i < w2-1 && i < w-1; i++)
            {
    
                for (int j =0; j < h2-1 && j < h-1; j++)
                { 
                    Color color = new Color(imagen.getRGB(i, j));
                    Color color2 = new Color(imagen2.getRGB(i, j));
                    int redacum = Math.round((color.getRed()   * imag1) + (color2.getRed()   * imag2));
                    int greenacum = Math.round((color.getGreen() * imag1) + (color2.getGreen() * imag2));
                    int blueacum = Math.round((color.getBlue()  * imag1) + (color2.getBlue()  * imag2));

                    newImage.setRGB(i,j,new Color(redacum, greenacum, blueacum).getRGB()); 
                    
                    
                }
            }*/
         
            
    

        //int rgb = imagen.getRGB(int x, int y);
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
            System.out.println("W " + w + " h " + h);      
         for (int i =0; i < w-1; i++)
         {
 
             for (int j =0; j < h-1; j++)
             {
                 double redacum = 0;
                 double greenacum = 0;
                 double blueacum = 0;
                 for (int x =0; x < matrix.length; x++)
                 {
                     for (int y =0; y < matrix.length; y++)
                     {
                        if ((i+(x-1) < w && j+(y-1) < h )&& (i+(x-1) > 0 && j+(y-1) > 0 ))
                        {

                           //System.out.println("wp " + (i+(x-1)) + " hp " + (j+(y-1)));
                            Color color = new Color(imagen.getRGB(i+(x-1), j+(y-1)));
                           
                            double red = (double)(color.getRed());
                            redacum = redacum + matrix[x][y] * red;
                            double green = (double)(color.getGreen());
                            greenacum = greenacum + matrix[x][y] * green;
                            double blue = (double)(color.getBlue());
                            blueacum = blueacum + matrix[x][y] * blue;
   
                            if (redacum > 255)
                            {
                                redacum = 255;
                            }
                           if (greenacum > 255)
                            {
                                greenacum = 255;
                            }
                           if (blueacum > 255)
                            {
                                blueacum = 255;
                            }
    
                            
                        }
                        else 
                        {
                            
                        }
                         
                        //System.out.println(matrix[x][y]);
                        
                          
                     }
                     
                  }
                  newImage.setRGB(i,j, new Color((int)redacum,(int)greenacum,(int)blueacum).getRGB());  
             }
             
         }*/

         //bordes
         /*double [][] matrix = {{0,1,0}, {1,-4,1}, {0,1,0}};
            System.out.println("W " + w + " h " + h);      
         for (int i =0; i < w-1; i++)
         {
 
             for (int j =0; j < h-1; j++)
             {
                 double redacum = 0;
                 double greenacum = 0;
                 double blueacum = 0;
                 for (int x =0; x < matrix.length; x++)
                 {
                     for (int y =0; y < matrix.length; y++)
                     {
                        if ((i+(x-1) < w && j+(y-1) < h )&& (i+(x-1) > 0 && j+(y-1) > 0 ))
                        {

                           //System.out.println("wp " + (i+(x-1)) + " hp " + (j+(y-1)));
                            Color color = new Color(imagen.getRGB(i+(x-1), j+(y-1)));
                            double red = (double)(color.getRed());
                            redacum = redacum + matrix[x][y] * red;
                            double green = (double)(color.getGreen());
                            greenacum = greenacum + matrix[x][y] * green;
                            double blue = (double)(color.getBlue());
                            blueacum = blueacum + matrix[x][y] * blue;
                            
                            
    
                            
                        }
                        
                         
                        //System.out.println(matrix[x][y]);
                        
                          
                     }
                     
                  }
                            if (redacum > 255)
                            {
                                redacum = 255; 
                            }
                            if (redacum < 0)
                            {
                                redacum = 0;
                            }
                
                           if (greenacum > 255)
                            {
                                greenacum = 255;
                            }
                            if (greenacum < 0)
                            {
                                greenacum = 0;
                            }
                           if (blueacum > 255)
                            {
                                blueacum = 255;
                            }
                            if (blueacum < 0)
                            {
                                blueacum = 0;
                            }
                  newImage.setRGB(i,j, new Color((int)redacum,(int)greenacum,(int)blueacum).getRGB());  
             }
             
         }*/

         //Sharpen Filter
         /*double [][] matrix = {{0,-1,0}, {-1,5,-1}, {0,-1,0}};
            //System.out.println("W " + w + " h " + h);      
         for (int i =0; i < w-1; i++)
         {
 
             for (int j =0; j < h-1; j++)
             {
                 double redacum = 0;
                 double greenacum = 0;
                 double blueacum = 0;
                 for (int x =0; x < matrix.length; x++)
                 {
                     for (int y =0; y < matrix.length; y++)
                     {
                        if ((i+(x-1) < w && j+(y-1) < h )&& (i+(x-1) > 0 && j+(y-1) > 0 ))
                        {

                           //System.out.println("wp " + (i+(x-1)) + " hp " + (j+(y-1)));
                            Color color = new Color(imagen.getRGB(i+(x-1), j+(y-1)));
                            double red = (double)(color.getRed());
                            redacum = redacum + matrix[x][y] * red;
                            double green = (double)(color.getGreen());
                            greenacum = greenacum + matrix[x][y] * green;
                            double blue = (double)(color.getBlue());
                            blueacum = blueacum + matrix[x][y] * blue;
                            
                            
    
                            
                        }
 
                     }
                     
                  }
                            if (redacum > 255)
                            {
                                redacum = 255; 
                            }
                            if (redacum < 0)
                            {
                                redacum = 0;
                            }
                
                           if (greenacum > 255)
                            {
                                greenacum = 255;
                            }
                            if (greenacum < 0)
                            {
                                greenacum = 0;
                            }
                           if (blueacum > 255)
                            {
                                blueacum = 255;
                            }
                            if (blueacum < 0)
                            {
                                blueacum = 0;
                            }
                  newImage.setRGB(i,j, new Color((int)redacum,(int)greenacum,(int)blueacum).getRGB());  
             }
             
         }*/
         //m.writeImage(smallImage,"starwars_big", "jpg");
         m.writeImage(bigImage,"starwars_small", "jpg");
    }
        
        
        
        
       
        
       
        //m.writeImage(imagen, "starwars_blur", "jpg");
       
        //System.out.println("mult"+ red);  

    
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
