package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class MapObj extends FlxSprite
	{
		[Embed(source = "assets/worlds/map_1/scene_1/obj1.png")] var MAP1_SCENE1_OBJ1:Class;
		[Embed(source = "assets/worlds/map_1/scene_1/obj2.png")] var MAP1_SCENE1_OBJ2:Class;
		public function MapObj(paramX:Number, paramY:Number,objid:uint) 
		{
			if(objid == 1)
				loadGraphic(MAP1_SCENE1_OBJ1, false, false, 640, 480);
			else if (objid == 2)
				loadGraphic(MAP1_SCENE1_OBJ2, false, false, 640, 480);
			this.x = paramX;
			this.y = paramY;
		}
		
	}

}