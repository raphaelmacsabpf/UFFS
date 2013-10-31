package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author 
	 */
	public class Caveira extends FlxSprite
	{
		[Embed(source = "../assets/Killer2.png")] public var ASSET_KILLER:Class;
		public function Caveira() 
		{
			loadGraphic(ASSET_KILLER, true, false, 129, 115);
		}
		
	}

}