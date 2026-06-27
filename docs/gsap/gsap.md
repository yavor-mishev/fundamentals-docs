# GSAP

### Timeline

The `timeline` class is a powerful tool for creating complex animations by sequencing multiple tweens together. It allows you to control the timing and order of your animations, making it easier to create smooth and coordinated effects. The main idea is to be able to chain multiple animations/tweens together and control their timing and order. You can add tweens to the timeline, and it will play them in sequence or at specific times.

Also using timelines we can control the timeline itself, for example we can pause, resume, reverse, or even seek to a specific point in the timeline. This gives you a lot of flexibility in how you manage your animations.

```ts
const timeline = gsap.timeline();

timeline
	.to(object, { x: 100, duration: 1 })
	.to(object, { y: 100, duration: 1 })
	.to(object, { x: 0, duration: 1 })
	.to(object, { y: 0, duration: 1 });

timeline.play(); // Start the timeline
timeline.pause(); // Pause the timeline
timeline.resume(); // Resume the timeline
timeline.reverse(); // Reverse the timeline
timeline.seek(2); // Seek to a specific point in the timeline (2 seconds)
```
