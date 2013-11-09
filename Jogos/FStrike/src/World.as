package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class World extends FlxSprite
	{
		[Embed(source = "assets/worlds/map_1/scene_1/scene1.png")] var ASSET_MAP1_SCENE1:Class;
		/*[Embed(source = "assets/worlds/map_1/scene_2/scene2.png")] var ASSET_MAP1_SCENE2:Class;
		[Embed(source = "assets/worlds/map_1/scene_3/scene3.png")] var ASSET_MAP1_SCENE3:Class;
		[Embed(source = "assets/worlds/map_1/scene_4/scene4.png")] var ASSET_MAP1_SCENE4:Class;
		[Embed(source = "assets/worlds/map_1/scene_5/scene5.png")] var ASSET_MAP1_SCENE5:Class;*/
		public function World(map:int,scene:int) 
		{
			if (map == 1)
				if (scene == 1)
					loadGraphic(ASSET_MAP1_SCENE1, false, false, 640, 480);
				
		}
		
	}

}