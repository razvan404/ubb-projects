package application.utils;

import javafx.animation.Animation;
import javafx.animation.Interpolator;
import javafx.animation.Transition;
import javafx.scene.Node;
import javafx.scene.effect.ColorAdjust;
import javafx.scene.effect.GaussianBlur;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Pane;
import javafx.util.Duration;

import java.util.UUID;

public final class Animations {
    private static final double DEFAULT_TRANSITION_DURATION = 250;
    private static final double DEFAULT_BOUNCE_DURATION = 2500;
    private static final double DEFAULT_BOUNCE_ANGLE = 10;
    private static double interpolateFunction(double oldSize, double newSize, double fraction) {
        return oldSize * (1 - fraction) + newSize * fraction;
    }

    public static Animation changeWidthTransition(Pane anchorPane, double oldSize, double newSize, double duration) {
        return new Transition() {
            {
                setCycleDuration(Duration.millis(duration));
            }

            @Override
            protected void interpolate(double fraction) {
                anchorPane.setPrefWidth(interpolateFunction(oldSize, newSize, fraction));
            }
        };
    }
    public static Animation changeWidthTransition(Pane anchorPane, double oldSize, double newSize) {
        return changeWidthTransition(anchorPane, oldSize, newSize, DEFAULT_TRANSITION_DURATION);

    }

    public static Animation changeHeightTransition(Pane anchorPane, double oldSize, double newSize, double duration) {
        return new Transition() {
            {
                setCycleDuration(Duration.millis(duration));
            }

            @Override
            protected void interpolate(double fraction) {
                anchorPane.setPrefHeight(interpolateFunction(oldSize, newSize, fraction));
            }
        };
    }

    public static Animation changeHeightTransition(Pane anchorPane, double oldSize, double newSize) {
        return changeHeightTransition(anchorPane, oldSize, newSize, DEFAULT_TRANSITION_DURATION);
    }

    public static Animation changeBlurTransition(Node node, double oldBlur, double newBlur, double duration) {
        return new Transition() {
            {
                setCycleDuration(Duration.millis(duration));
            }

            @Override
            protected void interpolate(double fraction) {
                node.setEffect(new GaussianBlur(interpolateFunction(oldBlur, newBlur, fraction)));
            }
        };
    }
    public static Animation changeBlurTransition(Node node, double oldBlur, double newBlur) {
        return changeBlurTransition(node, oldBlur, newBlur, DEFAULT_TRANSITION_DURATION);
    }

    public static Animation changeRightAnchorPaneTransition(Node node, double oldSize, double newSize, double duration) {
        return new Transition() {
            {
                setCycleDuration(Duration.millis(duration));
            }

            @Override
            protected void interpolate(double fraction) {
                AnchorPane.setRightAnchor(node, interpolateFunction(oldSize, newSize, fraction));
            }
        };
    }
    public static Animation changeRightAnchorPaneTransition(Pane anchorPane, double oldSize, double newSize) {
        return changeRightAnchorPaneTransition(anchorPane, oldSize, newSize, DEFAULT_TRANSITION_DURATION);

    }

    public static Animation hueTransition(Pane pane, double duration) {
        Transition transition = new Transition() {
            {
                setCycleDuration(Duration.millis(duration));
            }

            @Override
            protected void interpolate(double fraction) {
                ColorAdjust colorAdjust = new ColorAdjust();
                double val = interpolateFunction(0, 2, fraction);
                colorAdjust.setHue(val > 1 ? val - 2 : val);
                pane.setEffect(colorAdjust);
            }
        };
        transition.setCycleCount(Animation.INDEFINITE);
        transition.setInterpolator(Interpolator.LINEAR);
        return transition;
    }

    public static Animation bounceTransition(Node node, double angle, double duration) {
        Transition transition = new Transition() {
            {
                setCycleDuration(Duration.millis(duration));
            }

            @Override
            protected void interpolate(double fraction) {
                double val = interpolateFunction(0, 4 * angle, fraction);
                if (val <= angle) {
                    node.setRotate(val);
                }
                else if (val <= 3 * angle) {
                    node.setRotate(2 * angle - val);
                }
                else {
                    node.setRotate(val - 4 * angle);
                }
            }
        };
        transition.setCycleCount(Animation.INDEFINITE);
        transition.setInterpolator(Interpolator.LINEAR);
        return transition;
    }

    public static Animation bounceTransition(Node node) {
        return bounceTransition(node, DEFAULT_BOUNCE_ANGLE, DEFAULT_BOUNCE_DURATION);
    }

    public static Animation rotateTransition(Node node, double angle, double duration) {
        return new Transition() {
            {
                setCycleDuration(Duration.millis(duration));
            }

            @Override
            protected void interpolate(double fraction) {
                node.setRotate(interpolateFunction(0, angle, fraction));
            }
        };
    }

    public static Animation rotateTransition(Node node) {
        return rotateTransition(node, -180, DEFAULT_TRANSITION_DURATION);
    }

    public static ColorAdjust getColorAdjust(UUID identifier) {
        ColorAdjust colorAdjust = new ColorAdjust();
        colorAdjust.setHue(identifier.hashCode() * 1d / Integer.MAX_VALUE);
        return colorAdjust;
    }
}
