package  
{
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class Assets 
	{
		[Embed(source = "assets/backgrounds.png")] public static var BACKGROUND:Class;
		[Embed(source = "assets/player.png")] public static var ROBOT:Class;
		[Embed(source = "assets/block1.png")] public static var BLOCK1:Class;
		[Embed(source = "assets/playerCollisor.png")] public static var PLAYERCOLLISOR:Class;
		public function Assets() 
		{
		
		}
		
	}

}