package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class EnemySpawnPoint extends FlxBasic
	{
		public var point:FlxPoint;
		public var size:String;
		public var angle:uint;
		public function EnemySpawnPoint(p:FlxPoint, size:String, angle:uint) 
		{
			this.point = p;
			this.size = size;
			this.angle = angle;
		}
	}

}