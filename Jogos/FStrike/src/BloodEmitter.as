package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class BloodEmitter extends FlxObject
	{
		
		var aEmitter:FlxEmitter;
		public function BloodEmitter() 
		{
			
		}
		public function create():FlxEmitter
		{
				aEmitter = new FlxEmitter();
				aEmitter.makeParticles(ASSET_BLOOD1, 16, 32, true, 0);
				aEmitter.setXSpeed(-350, 350);
				aEmitter.setYSpeed( -150, 10);
				aEmitter.setRotation( -720, 720);
				aEmitter.gravity = 100;
				aEmitter.at(
				return aEmitter;
		}
	}

}