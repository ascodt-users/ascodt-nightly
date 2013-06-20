//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package de.tum.charts;

import java.text.DecimalFormat;


public class LinePlotterBasisJavaImplementation extends de.tum.charts.LinePlotterAbstractJavaImplementation {
	public class Measurement {
		public double x[];
		public double y[];
		public String label;

		/**
		 * @return Label of a measurement
		 */
		public String getLabelForPlot() {
			return label + " (" + getMinOfYValues() + "," + getMaxOfYValues() + ";#" + x.length + ")";
		}

		/**
		 * @return Minimum of measured values
		 */
		public double getMinOfYValues() {
			if (y.length==0) return 0.0;

			double result = java.lang.Double.MAX_VALUE;
			for (int j=0; j<y.length; j++) {
				if (y[j]<result) result = y[j];
			}
			return result;
		}

		/**
		 * @return Maximum of measured values
		 */
		public double getMaxOfYValues() {
			if (y.length==0) return 0.0;

			double result = java.lang.Double.MIN_VALUE;
			for (int j=0; j<y.length; j++) {
				if (y[j]>result) result = y[j];
			}
			return result;
		}

		/**
		 * Scales the x value with respect to the max and min of all the 
		 * measurements.
		 * 
		 * @return Scaled x value.  
		 */
		public int getScaledX(int entry, double min, double max, int xSize) {
			double scale   = max - min;
			double result  = x[entry];
			if (scale<=0.0) scale = 1.0;
			result -= min;
			result /= scale;
			result *= xSize;
			return (int)java.lang.Math.round(result);
		}

		public boolean hasNiveauLineDifferentToXAxis() {
			return getMinOfYValues() != 0.0;
		}

		public int getNiveauLine(int ySize) {
			if (getMinOfYValues()>0.0) {
				return getScaledY(getMinOfYValues(),ySize);
			}
			else {
				return getScaledY(0.0,ySize);
			}
		}
		public String getNiveauLineLabel() {
			assert( hasNiveauLineDifferentToXAxis() );
			final DecimalFormat decimalFormat = new DecimalFormat("0.#####E00");
			return decimalFormat.format(getMinOfYValues());
		}

		/**
		 * The scaling of data is very simple: We compute the total delta  of the 
		 * measurement and divide the value through it, i.e. this difference is 
		 * the scaling. Things are different if the measurements all have the same 
		 * value. In this case, I return a scaling of one to avoid a division by 
		 * zero. 
		 * 
		 * Finally, I also make the scale increase if the whole simulation has a 
		 * niveau offset (see getNiveauOffset()).
		 */
		private double getScale() {
			double scale   = getMaxOfYValues() - getMinOfYValues();
			if (scale<=0.0) scale = 1.0;
			scale         *= (1.0+getNiveauOffset()); 
			return scale;
		}

		/**
		 * Usually, the niveau offset equals zero. There's only one exception: If 
		 * the smallest measurement is bigger than zero, it does not make sense to 
		 * plot the whole results starting from the x-axis, i.e. to make the x-axis 
		 * the smallest value. This would induce a wrong (visual) interpretation. 
		 * 
		 * @return
		 */
		private double getNiveauOffset() {
			if (getMinOfYValues()>0.0) {
				return 0.2;
			}
			else {
				return 0.0;
			}
		}

		/**
		 * Takes a measurement and scaled it. This process has several steps: 
		 *  
		 * - Translate the measurement such that 
		 * @param value
		 * @param ySize
		 * @return
		 */
		private int getScaledY(double value, int ySize) {
			value -= getMinOfYValues();
			value /= getScale();
			value += getNiveauOffset();
			value *= ySize;
			return (int)java.lang.Math.round(value);
		}

		/**
		 * Takes the entryth value of the measurement and forwards this value to 
		 * the scaling operation getScaledY().
		 */
		public int getScaledY(int entry, int ySize) {
			return getScaledY(y[entry], ySize);
		}
	}

	protected String                        _xLabel;
	protected String                        _yLabel;
	protected String                        _title;
	protected java.util.Vector<Measurement> _measurements;
	protected LinePlotterUI _ui;
	/**
	 * Remove a measurement. This operation is save, i.e. if the measurement 
	 * does not exist, the operation just becomes nop. 
	 */
	private void removeMeasurement(String label) {
		int currentMeasurement = 0;
		while (currentMeasurement<_measurements.size()) {
			if (_measurements.get(currentMeasurement).label.equals(label)) {
				_measurements.remove(currentMeasurement);
				return;
			}
			currentMeasurement++;
		}
	}

	public void plotPoint(String label, double x, double y) {
		removeMeasurement(label);
		Measurement newMeasurement = new Measurement();
		newMeasurement.label       = label;
		newMeasurement.x           = new double[1];
		newMeasurement.y           = new double[1];
		newMeasurement.x[0]        = x;
		newMeasurement.y[0]        = y;
		_measurements.add(newMeasurement);
		_ui.redraw();
	}

	public void plotCurve(String label, double[] x, double[] y) {
		if (x.length != y.length) {

			System.err.println("set of x and y measurement don't have the same length" );

		}
		else {
			removeMeasurement(label);
			Measurement newMeasurement = new Measurement();
			newMeasurement.label       = label;
			newMeasurement.x           = new double[x.length];
			newMeasurement.y           = new double[x.length];
			for (int i=0; i<x.length; i++) {
				newMeasurement.x[i]        = x[i];
				newMeasurement.y[i]        = y[i];
			}
			_measurements.add(newMeasurement);
			_ui.redraw();
		}
	}
	public LinePlotterBasisJavaImplementation( String identifier ) {
		super(identifier);
	}


	public void setTitle(String title) {
		_title = title;
	}

	public void setXLabel(String label) {
		_xLabel = label;
	}

	public void setYLabel(String label) {
		_yLabel = label;
	}

	@Override
	public void removePlot(String label) {
		removeMeasurement(label);
	}

	@Override
	public void clear() {
		_measurements = new java.util.Vector<Measurement>();
		_ui.redraw();
	}

	/**
	 * Provides methods block
	 */

}


